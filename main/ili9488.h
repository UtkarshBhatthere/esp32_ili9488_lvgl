#ifndef _ILI9488_H_
#define _ILI9488_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_essentials.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "esp_log.h"

/* TFT Pins */
#define ili_DC      19
#define ili_RST     18
#define ili_BCKL    23

/* Commands for ILI9488 */
#define iliCMD_NOP                          (uint8_t)(0x00)
#define iliCMD_SOFT_RESET                   (uint8_t)(0x01)
#define iliCMD_R_ID                         (uint8_t)(0x04)
#define iliCMD_R_NO_ERRORS                  (uint8_t)(0x05)
#define iliCMD_R_STATUS                     (uint8_t)(0x09)
#define iliCMD_R_POWER_MODE                 (uint8_t)(0x0A)
#define iliCMD_R_MADCTL                     (uint8_t)(0x0B)
#define iliCMD_R_PXL_FORMAT                 (uint8_t)(0x0C)
#define iliCMD_R_IMG_MODE                   (uint8_t)(0x0D)
#define iliCMD_R_SGNL_MODE                  (uint8_t)(0x0E)
#define iliCMD_R_DIAGNOSTIC_RESULT          (uint8_t)(0x0F)
#define iliCMD_SLEEP_IN                     (uint8_t)(0x10)
#define iliCMD_SLEEP_OUT                    (uint8_t)(0x11)
#define iliCMD_PARTIAL_MODE_ON              (uint8_t)(0x12)
#define iliCMD_NORMAL_MODE_ON               (uint8_t)(0x13)
#define iliCMD_INVERSION_OFF                (uint8_t)(0x20)
#define iliCMD_INVERSION_ON                 (uint8_t)(0x21)
#define iliCMD_ALL_PXL_OFF                  (uint8_t)(0x22)
#define iliCMD_ALL_PXL_ON                   (uint8_t)(0x23)
#define iliCMD_DISPLAY_OFF                  (uint8_t)(0x28)
#define iliCMD_DISPLAY_ON                   (uint8_t)(0x29)
#define iliCMD_COLUMN_ADDR_SET              (uint8_t)(0x2A)
#define iliCMD_PAGE_ADDR_SET                (uint8_t)(0x2B)
#define iliCMD_MEMORY_WRITE                 (uint8_t)(0x2C)
#define iliCMD_MEMORY_READ                  (uint8_t)(0x2E)
#define iliCMD_PARTIAL_AREA                 (uint8_t)(0x30)
#define iliCMD_VERTICAL_SCROLLING_DEFN      (uint8_t)(0x33)
#define iliCMD_TEARING_EFFECT_LINE_OFF      (uint8_t)(0x34)
#define iliCMD_TEARING_EFFECT_LINE_ON       (uint8_t)(0x35)
#define iliCMD_MEM_ACCESS_CTRL              (uint8_t)(0x36)
#define iliCMD_VER_SCRL_STRT_ADDR           (uint8_t)(0x37)
#define iliCMD_IDLE_MODE_OFF                (uint8_t)(0x38)
#define iliCMD_IDLE_MODE_ON                 (uint8_t)(0x39)
#define iliCMD_INTRFC_PIXEL_FORMAT          (uint8_t)(0x3A)
#define iliCMD_MEMORY_WRITE_CONT            (uint8_t)(0x3C)
#define iliCMD_MEMORY_READ_CONT             (uint8_t)(0x3E)
#define iliCMD_W_TEAR_SCAN_LINE             (uint8_t)(0x44)
#define iliCMD_R_TEAR_SCAN_LINE             (uint8_t)(0x45)
#define iliCMD_W_DISPLAY_BRIGHTNESS         (uint8_t)(0x51)
#define iliCMD_R_DISPLAY_BRIGHTNESS         (uint8_t)(0x52)
#define iliCMD_W_CTRL_DISPLAY_VALUE         (uint8_t)(0x53)
#define iliCMD_R_CTRL_DISPLAY_VALUE         (uint8_t)(0x54)
#define iliCMD_W_CNTNT_ADPTV_BRGHTNS_VALUE  (uint8_t)(0x55)
#define iliCMD_R_CNTNT_ADPTV_BRGHTNS_VALUE  (uint8_t)(0x56)
#define iliCMD_W_CABC_MIN_BRGTHNS           (uint8_t)(0x5E)
#define iliCMD_R_CABC_MIN_BRGTHNS           (uint8_t)(0x5F)
#define iliCMD_R_ATMTC_BRGTHNS_CTRL_RSLT    (uint8_t)(0x68)
#define iliCMD_R_ID1                        (uint8_t)(0xDA)
#define iliCMD_R_ID2                        (uint8_t)(0xDB)
#define iliCMD_R_ID3                        (uint8_t)(0xDC)

//CUSTOM
// If High bit set, Delay follows.
#define iliCMD_DELAY	                    (uint8_t)(0x80)

/* Extended Command List */
#define iliCMD_INTRFC_MODE_CTRL             (uint8_t)(0xB0)
#define iliCMD_FRAME_RATE_CTRL_NRML         (uint8_t)(0xB1)
#define iliCMD_FRAME_RATE_CTRL_IDLE         (uint8_t)(0xB2)
#define iliCMD_FRAME_RATE_CTRL_PRTL         (uint8_t)(0xB3)
#define iliCMD_DISPLAY_INVERSION_CTRL       (uint8_t)(0xB4)
#define iliCMD_BLANKING_PORCH_CTRL          (uint8_t)(0xB5)
#define iliCMD_DISPLAY_FUNCTION_CTRL        (uint8_t)(0xB6)
#define iliCMD_ENTRY_MODE_SET               (uint8_t)(0xB7)
#define iliCMD_COLOR_ENHNCMNT_CONTROL_1     (uint8_t)(0xB9)
#define iliCMD_COLOR_ENHNCMNT_CONTROL_2     (uint8_t)(0xBA)
#define iliCMD_HS_LANES_CTRL                (uint8_t)(0xBE)
#define iliCMD_PWR_CTRL_1                   (uint8_t)(0xC0)
#define iliCMD_PWR_CTRL_2                   (uint8_t)(0xC1)
#define iliCMD_PWR_CTRL_3                   (uint8_t)(0xC2)
#define iliCMD_PWR_CTRL_4                   (uint8_t)(0xC3)
#define iliCMD_PWR_CTRL_5                   (uint8_t)(0xC4)
#define iliCMD_VCOM_CTRL_1                  (uint8_t)(0xC5)
#define iliCMD_CABC_CTRL_1                  (uint8_t)(0xC6)
#define iliCMD_CABC_CTRL_2                  (uint8_t)(0xC8)
#define iliCMD_CABC_CTRL_3                  (uint8_t)(0xC9)
#define iliCMD_CABC_CTRL_4                  (uint8_t)(0xCA)
#define iliCMD_CABC_CTRL_5                  (uint8_t)(0xCB)
#define iliCMD_CABC_CTRL_6                  (uint8_t)(0xCC)
#define iliCMD_CABC_CTRL_7                  (uint8_t)(0xCD)
#define iliCMD_CABC_CTRL_8                  (uint8_t)(0xCE)
#define iliCMD_CABC_CTRL_9                  (uint8_t)(0xCF)
#define iliCMD_NV_MEMORY_WRITE              (uint8_t)(0xD0)
#define iliCMD_NV_MEMORY_PROTECTION_KEY     (uint8_t)(0xD1)
#define iliCMD_NV_MEMORY_STATUS_READ        (uint8_t)(0xD2)
#define iliCMD_READ_ID_4                    (uint8_t)(0xD3)
#define iliCMD_ADJUST_CONTROL_1             (uint8_t)(0xD7)
#define iliCMD_READ_ID4_CHECK               (uint8_t)(0xD8)
#define iliCMD_PGAMACTRL                    (uint8_t)(0xE0)
#define iliCMD_NGAMACTRL                    (uint8_t)(0xE1)
#define iliCMD_DGTL_GAMMA_CTRL_1            (uint8_t)(0xE2)
#define iliCMD_DGTL_GAMMA_CTRL_2            (uint8_t)(0xE3)
#define iliCMD_SET_IMAGE_FUNCTION           (uint8_t)(0xE9)
#define iliCMD_ADJUST_CTRL_2                (uint8_t)(0xF2)
#define iliCMD_ADJUST_CTRL_3                (uint8_t)(0xF7)
#define iliCMD_ADJUST_CTRL_4                (uint8_t)(0xF8)
#define iliCMD_ADJUST_CTRL_5                (uint8_t)(0xF9)
#define iliCMD_SPI_READ_CMD_SETTING         (uint8_t)(0xFB)
#define iliCMD_ADJUST_CTRL_6                (uint8_t)(0xFC)
#define iliCMD_ADJUST_CTRL_7                (uint8_t)(0xFF)

/* API's */
void iliInit(void);
void iliFill(int32_t x1, int32_t y1, int32_t x2, int32_t y2, lv_color_t color);
void iliFlush(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const lv_color_t * color_map);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif