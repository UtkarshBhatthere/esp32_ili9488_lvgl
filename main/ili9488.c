#include "ili9488.h"

/* Init Sequence */
static const uint8_t displayInit[] = {
  17,                    					        // 17 commands in list
  iliCMD_PGAMACTRL, 15, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,
  iliCMD_NGAMACTRL, 15,	0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,
  iliCMD_PWR_CTRL_1, 2, 0x17, 0x15,                 //Vreg1out, Verg2out
  iliCMD_PWR_CTRL_2, 1, 0x41,                       //VGH,VGL
  iliCMD_VCOM_CTRL_1,3, 0x00, 0x12, 0x80,           //Vcom
  iliCMD_MEM_ACCESS_CTRL, 1, (0x20 | 0x00),		    // Memory Access Control (orientation), Portrait | RGB Matrix.
  iliCMD_INTRFC_PIXEL_FORMAT, 1, 0x55,              // 0x55 -> 16 bit 0x66 -> 18 bit
  iliCMD_INTRFC_MODE_CTRL, 1, 0x00,                 // 0x80: SDO NOT USE; 0x00 USE SDO
  iliCMD_FRAME_RATE_CTRL_NRML, 1, 0xA0,             //60Hz
  iliCMD_DISPLAY_INVERSION_CTRL, 1, 0x02,           //2-dot
  iliCMD_DISPLAY_FUNCTION_CTRL, 2, 0x02, 0x02,      // MCU, Source,Gate scan direction
  iliCMD_SET_IMAGE_FUNCTION, 1, 0x00,               // Disable 24 bit data
  iliCMD_W_CTRL_DISPLAY_VALUE, 1, 0x28,             // BCTRL && DD on
  iliCMD_W_DISPLAY_BRIGHTNESS, 1, 0x7F,
  iliCMD_ADJUST_CTRL_3, 4, 0xA9, 0x51, 0x2C, 0x02,  // D7 stream, loose
  iliCMD_SLEEP_OUT, iliCMD_DELAY, 120,              //Exit Sleep
  iliCMD_DISPLAY_ON, 0,                             //Display on
};

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void ili_send_cmd(uint8_t cmd)
{
	gpio_set_level(ili_DC, 0);	 /*Command mode*/
	spiSendData(&cmd, 1);
}

static void ili_send_data(void * data, uint16_t length)
{
	gpio_set_level(ili_DC, 1);	 /*Data mode*/
	spiSendData(data, length);
}

static void ili_send_color(void * data, uint16_t length)
{
    gpio_set_level(ili_DC, 1);   /*Data mode*/
    spiSendColor(data, length);
}

/* API's */
void iliInit(void)
{
		uint8_t* addr = displayInit;
    uint8_t  numCommands, numArgs, cmd;
    uint16_t ms;
    //Initialize non-SPI GPIOs
	gpio_set_direction(ili_DC, GPIO_MODE_OUTPUT);
	gpio_set_direction(ili_RST, GPIO_MODE_OUTPUT);
	gpio_set_direction(ili_BCKL, GPIO_MODE_OUTPUT);

    //Reset the display
	gpio_set_level(ili_RST, 0);
	vTaskDelay(100 / portTICK_RATE_MS);
	gpio_set_level(ili_RST, 1);
	vTaskDelay(100 / portTICK_RATE_MS);

    ESP_LOGI("[ILI9488]", "Initialising");

    numCommands = *addr++;				// Number of commands to follow
    while(numCommands--) {				// For each command...
    cmd = *addr++;						// save command
    numArgs  = *addr++;					// Number of args to follow
    ms       = numArgs & iliCMD_DELAY;	// If high bit set, delay follows args
    numArgs &= ~iliCMD_DELAY;			// Mask out delay bit

    ili_send_cmd(cmd);                          //Send Command.
    ili_send_data((uint8_t *)addr, numArgs);    //Send respective Data.
	addr += numArgs;                            //Shift pointer to next cmd.

    if(ms) {
      ms = *addr++;              // Read post-command delay time (ms)
	  vTaskDelay(ms / portTICK_RATE_MS);
    }
    gpio_set_level(ili_BCKL, 1);
  }
}

void iliFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color)
{
	uint8_t data[4];

	/*Column addresses*/
	ili_send_cmd(iliCMD_COLUMN_ADDR_SET);
	data[0] = (x1 >> 8) & 0xFF;
	data[1] = x1 & 0xFF;
	data[2] = (x2 >> 8) & 0xFF;
	data[3] = x2 & 0xFF;
	ili_send_data(data, 4);

	/*Page addresses*/
	ili_send_cmd(iliCMD_PAGE_ADDR_SET);
	data[0] = (y1 >> 8) & 0xFF;
	data[1] = y1 & 0xFF;
	data[2] = (y2 >> 8) & 0xFF;
	data[3] = y2 & 0xFF;
	ili_send_data(data, 4);

	/*Memory write*/
	ili_send_cmd(iliCMD_MEMORY_WRITE);

	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);
	uint16_t buf[LV_HOR_RES];

	uint32_t i;
	if(size < LV_HOR_RES) {
		for(i = 0; i < size; i++) buf[i] = color.full;

	} else {
		for(i = 0; i < LV_HOR_RES; i++) buf[i] = color.full;
	}

	while(size > LV_HOR_RES) {
		ili_send_color(buf, LV_HOR_RES * 2);
		size -= LV_HOR_RES;
	}

	ili_send_color(buf, size * 2);	/*Send the remaining data*/
}

void iliFlush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_map)
{
	uint8_t data[4];

	/*Column addresses*/
	ili_send_cmd(0x2A);
	data[0] = (x1 >> 8) & 0xFF;
	data[1] = x1 & 0xFF;
	data[2] = (x2 >> 8) & 0xFF;
	data[3] = x2 & 0xFF;
	ili_send_data(data, 4);

	/*Page addresses*/
	ili_send_cmd(0x2B);
	data[0] = (y1 >> 8) & 0xFF;
	data[1] = y1 & 0xFF;
	data[2] = (y2 >> 8) & 0xFF;
	data[3] = y2 & 0xFF;
	ili_send_data(data, 4);

	/*Memory write*/
	ili_send_cmd(0x2C);

	uint32_t size = (x2 - x1 + 1) * (y2 - y1 + 1);

	ili_send_color((void*)color_map, size * 2);	/*Send the remaining data*/
}