/**
 * @file lv_test_img.h
 *
 */

#ifndef LV_TEST_IMG_H
#define LV_TEST_IMG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#include "lv_ex_conf.h"
#else
#include "../../../../lvgl/lvgl.h"
#include "../../../../lv_ex_conf.h"
#endif

#if USE_LV_IMG && USE_LV_TESTS

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create images to test their functionalities
 */
void lv_test_img_1(void);

/**********************
 *      MACROS
 **********************/

#endif /*USE_LV_IMG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*USE_LV_IMG && USE_LV_TESTS*/
