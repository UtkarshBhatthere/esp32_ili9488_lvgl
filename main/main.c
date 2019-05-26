/* SPI Master example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "../components/lvgl/lvgl.h"
#include "../components/lv_examples/lv_apps/demo/demo.h"
#include "esp_freertos_hooks.h"

#include "ili9488.h"

static void IRAM_ATTR lv_tick_task(void);

void app_main()
{
	lv_init();

	spiInit();
	iliInit();

	lv_disp_drv_t disp;
	lv_disp_drv_init(&disp);
	disp.disp_flush = iliFlush;
    disp.disp_fill = iliFill;
	lv_disp_drv_register(&disp);

	esp_register_freertos_tick_hook(lv_tick_task);

	demo_create();

	while(1) {
		vTaskDelay(1);
		lv_task_handler();
	}
}

static void IRAM_ATTR lv_tick_task(void)
{
	lv_tick_inc(portTICK_RATE_MS);
}
