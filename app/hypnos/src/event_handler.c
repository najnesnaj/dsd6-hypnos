/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <drivers/sensor/cst816s.h>
#include <stdbool.h>
#include "battery.h"
#include "bt.h"
#include "clock.h"
#include "display.h"
#include "event_handler.h"
#include "gui.h"
#include "log.h"

/* ********** defines ********** */
#define BAT_CHA 2 //jj
#define BTN_PORT DT_GPIO_LABEL(DT_ALIAS(sw0), gpios)
#define BTN_IN  DT_GPIO_PIN(DT_ALIAS(sw0), gpios)
#define BTN_OUT 3 //jj 
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_DOUBLE_EDGE)
#define PULL_UP DT_GPIO_FLAGS(DT_ALIAS(sw0), gpios)
#define DISPLAY_TIMEOUT K_SECONDS(5)
#ifdef CONFIG_BOOTLOADER_MCUBOOT
/* The watchdog released by the PineTime bootloader v5.0.0-rc1
 * will try to bite every 7 seconds.
 */
#define WDT_REFRESH 6
#endif
/* ********** ******* ********** */

/* ********** variables ********** */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
static struct k_timer watchdog_refresh_timer;
#endif
static struct k_timer display_off_timer;
static const struct device *charging_dev;
static struct gpio_callback charging_cb;
static const struct device *button_dev;
//static struct gpio_callback button_cb;
static struct gpio_callback button_cb;

/* ********** ********* ********** */

/* ********** init function ********** */
void event_handler_init()
{
	/* Initialize GPIOs */
	charging_dev = device_get_binding("GPIO_0");
	gpio_pin_configure(charging_dev, BAT_CHA, GPIO_INPUT | GPIO_INT_EDGE_BOTH);
	gpio_init_callback(&charging_cb, battery_charging_isr, BIT(BAT_CHA));
	button_dev = device_get_binding(BTN_PORT);
	gpio_pin_configure(button_dev, BTN_IN, GPIO_INPUT | GPIO_INT_EDGE_FALLING | PULL_UP);
	gpio_init_callback(&button_cb, button_pressed_isr, BIT(BTN_IN));

	/* Enable GPIOs */
	gpio_add_callback(charging_dev, &charging_cb);
	gpio_add_callback(button_dev, &button_cb);

	/* Set button out pin to high to enable the button */
	uint32_t button_out = 1U;
	gpio_pin_configure(button_dev, BTN_OUT, GPIO_OUTPUT);
	gpio_pin_set_raw(button_dev, BTN_OUT, button_out);

	/* Start timers */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
	if (NRF_WDT->RUNSTATUS) {
		LOG_INF("Watchdog detected. Let's kick it every %d seconds.",
			WDT_REFRESH);
		k_timer_init(&watchdog_refresh_timer, watchdog_refresh_isr,
			     NULL);
		k_timer_start(&watchdog_refresh_timer, K_NO_WAIT,
			      K_SECONDS(WDT_REFRESH));
	} else {
		LOG_INF("No watchdog detected.");
	}
#endif
	k_timer_init(&display_off_timer, display_off_isr, NULL);
	k_timer_start(&display_off_timer, DISPLAY_TIMEOUT, K_NO_WAIT);

	/* Special cases */
	/* Get battery charging status */
	k_sleep(K_MSEC(10));
	uint32_t res =  gpio_pin_get(charging_dev, BAT_CHA);
	battery_update_charging_status(res != 1U);

	/* Show time, date and battery status */
	clock_show_time();
	battery_show_status();

	LOG_DBG("Event handler init: Done");
}
/* ********** ************ ********** */

/* ********** interrupt handlers ********** */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
void watchdog_refresh_isr(struct k_timer *wdt_refresh)
{
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;
}
#endif

void display_off_isr(struct k_timer *light_off)
{
//	backlight_enable(false);
	display_sleep();
}

void battery_charging_isr(const struct device *gpiobat, struct gpio_callback *cb, uint32_t pins)
{
	uint32_t res = gpio_pin_get(charging_dev, BAT_CHA);
	battery_update_charging_status(res != 1U);
}

void button_pressed_isr(const struct device *gpiobtn, struct gpio_callback *cb, uint32_t pins)
{
	display_wake_up();
	//backlight_enable(true);
	k_timer_start(&display_off_timer, DISPLAY_TIMEOUT, K_NO_WAIT);

	gui_handle_button_event();
}


/* ********** ************** ********** */
