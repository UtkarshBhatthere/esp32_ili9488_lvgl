#include "spi_essentials.h"


/* Internal API's */
static void IRAM_ATTR queue_ready (spi_transaction_t *trans);

/* Internal Var's */
static spi_device_handle_t spi;
static volatile bool spi_trans_in_progress;
static volatile bool spi_color_sent;

/* API's */
void spiInit(void)
{

    esp_err_t ret;

    spi_bus_config_t buscfg={
            .miso_io_num=-1,
            .mosi_io_num=spi_MOSI,
            .sclk_io_num=spi_CLK,
            .quadwp_io_num=-1,
            .quadhd_io_num=-1,
            .max_transfer_sz = LV_VDB_SIZE * 2,
    };

    spi_device_interface_config_t devcfg={
            .clock_speed_hz=80*1000*1000,           //Clock out at 80 MHz
            .mode=0,                                //SPI mode 0
            .spics_io_num=spi_CS,                   //CS pin
            .queue_size=1,
            .pre_cb=NULL,
            .post_cb=queue_ready,
    };

    //Initialize the SPI bus
    ret=spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    assert(ret==ESP_OK);

    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    assert(ret==ESP_OK);
}

void spiSendData(uint8_t *data, uint16_t length)
{
    if (length == 0) return;           //no need to send anything

    while(spi_trans_in_progress);       //Usually doesn't blocks for long.

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       	//Zero out the transaction
    t.length = length * 8;              //Length is in bytes, transaction length is in bits.
    t.tx_buffer = data;               	//Data
    spi_trans_in_progress = true;
    spi_color_sent = false;             //Mark the "lv_flush_ready" NOT needs to be called in "spi_ready"
    spi_device_queue_trans(spi, &t, portMAX_DELAY);
}

void spiSendColor(uint8_t * colorMap, uint16_t length)
{
    if (length == 0) return;           //no need to send anything

    while(spi_trans_in_progress);       //Usually doesn't blocks for long, Check and add a NB Delay if required.

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));           //Zero out the transaction
    t.length = length * 8;              //Length is in bytes, transaction length is in bits.
    t.tx_buffer = colorMap;                 //Data
    spi_trans_in_progress = true;
    spi_color_sent = true;              //Mark the "lv_flush_ready" needs to be called in "spi_ready"
    spi_device_queue_trans(spi, &t, portMAX_DELAY);
}

// callback for SPI post action.
static void IRAM_ATTR queue_ready (spi_transaction_t *trans)
{
    spi_trans_in_progress = false;

    if(spi_color_sent) lv_flush_ready();
}