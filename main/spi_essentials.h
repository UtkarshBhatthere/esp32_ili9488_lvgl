#ifndef _SPI_ESSENTIALS_H_
#define _SPI_ESSENTIALS_H_

/* This is Ported Code from LVGL ili9431 example code. */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include "stdint.h"
#include "../components/lvgl/lvgl.h"
#include "driver/spi_master.h"

// They Go Here.

/* Pinout */
// MISO will not be required since we're just dealing with the LCD output interface.
// Fill in the Pinout values acc to HSPI or VSPI. Currently HSPI
#define spi_MOSI 13
#define spi_CLK  14
#define spi_CS   15

/* API's */
void spiInit(void);
void spiSendData(uint8_t * data, uint16_t length);
void spiSendColor(uint8_t * colorMap, uint16_t length);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // _SPI_ESSENTIALS_H_