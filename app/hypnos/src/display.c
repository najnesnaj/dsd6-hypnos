/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/display.h>
#include <device.h>
#include <display/cfb.h>
//#include <display.h>
#include "display.h"
#include "log.h"

/* ********** ********** VARIABLES AND STRUCTS ********** ********** */
const struct device *display_dev;
/* ********** ********** ********** ********** ********** ********** */

/* ********** ********** FUNCTIONS ********** ********** */
void display_init(void)
{
	display_dev = device_get_binding("SSD1306");
display_blanking_on(display_dev);
//	display_blanking_off(display_dev);
	LOG_INF("Display init: Done");
}

void display_sleep(void)
{
// 	(void)device_set_power_state(display_dev, DEVICE_PM_LOW_POWER_STATE, NULL,
//				     NULL);
display_blanking_on(display_dev);

}

void display_wake_up(void)
{
//	(void)device_set_power_state(display_dev, DEVICE_PM_ACTIVE_STATE, NULL,
//				     NULL);
display_blanking_off(display_dev);
}


/* ********** ********** ********** ********** ********** */
