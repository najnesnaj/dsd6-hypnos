/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <lvgl.h>
#include "gfx.h"
#include "log.h"
#include "version.h"
#include <string.h>

/* ********** Macros and constants ********** */
LV_FONT_DECLARE(rubik_regular_68);
LV_FONT_DECLARE(rubik_regular_34);

#define BAT_LABEL_MARGIN 3
/* ********** ******* ********** */

/* ********** Variables ********** */
static lv_obj_t *battery_label;
static lv_obj_t *bt_label;
//lv_obj_t *time_label2;
lv_obj_t *time_label;
static lv_obj_t *date_label;
static lv_obj_t *info_label;
//lv_obj_t *hello_world_label; //jj
//static lv_style_t style;
//static lv_style_t style_time;
//static lv_style_t style_date;

/* ********** Functions ********** */
void gfx_init(void)
{
	/* Create styles for time, date and the rest */
//	lv_style_copy(&style, &lv_style_plain);
//	lv_style_copy(&style_time, &lv_style_plain);
//	lv_style_copy(&style_date, &lv_style_plain);

	/* Default style */
//	style.body.main_color = LV_COLOR_BLACK;
//	style.body.grad_color = LV_COLOR_BLACK;
//	style.text.color = LV_COLOR_WHITE;
//	style.text.font = &lv_font_roboto_22;
//	lv_obj_set_style(lv_scr_act(), &style);

// jj test
        time_label = lv_label_create(lv_scr_act(), NULL);
//      lv_label_set_style(time_label, LV_LABEL_STYLE_MAIN, &style_time);
        lv_label_set_text(time_label, "00:00");
        lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, 0); //jj


//	hello_world_label = lv_label_create(lv_scr_act(), NULL);
//lv_label_set_text(hello_world_label, "tijd is nu  12:23");
 //       lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 8);



	/* Battery label */
//	battery_label = lv_label_create(lv_scr_act(), NULL);
//	lv_label_set_style(battery_label, LV_LABEL_STYLE_MAIN, &style);
//	lv_label_set_text(battery_label, "");

	/* Bluetooth label */
	bt_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(bt_label, NULL,  LV_ALIGN_CENTER, 10, -8);
//	lv_label_set_style(bt_label, LV_LABEL_STYLE_MAIN, &style);
	lv_label_set_text(bt_label, LV_SYMBOL_WIFI);

	/* Time label and style */
//	style_time.body.main_color = LV_COLOR_BLACK;
//	style_time.body.grad_color = LV_COLOR_BLACK;
//	style_time.text.font = &rubik_regular_68;

//	style_time.text.color = LV_COLOR_WHITE;
//	style_time.text.color = LV_COLOR_WHITE;
//	lv_obj_set_style(lv_scr_act(), &style_time);
//	time_label = lv_label_create(lv_scr_act(), NULL);
//	lv_label_set_style(time_label, LV_LABEL_STYLE_MAIN, &style_time);
//	lv_label_set_text(time_label, "00:00");
//	lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, 0); //jj
/*
	info_label = lv_label_create(lv_scr_act(), NULL);
//	lv_label_set_style(info_label, LV_LABEL_STYLE_MAIN, &style);
	if (strlen(FW_VERSION) < 10) {
		lv_label_set_text(info_label, "Hypnos " FW_VERSION "\n\n"
				  "This is Free Software" "\n"
				  "without any warranty." "\n\n"
				  "https://github.com/"   "\n"
				  "endian-albin/"         "\n"
				  "pinetime-hypnos");
	} else {
		lv_label_set_text(info_label, "Hypnos"    "\n"
				  FW_VERSION              "\n\n"
				  "This is Free Software" "\n"
				  "without any warranty." "\n"
				  "https://github.com/"   "\n"
				  "endian-albin/"         "\n"
				  "pinetime-hypnos");
	}
	lv_obj_set_hidden(info_label, true);
*/
	/* Date label and style */
//	style_date.body.main_color = LV_COLOR_BLACK;
//	style_date.body.grad_color = LV_COLOR_BLACK;
//	style_date.text.font = &rubik_regular_34;
//	style_date.text.color = LV_COLOR_YELLOW;
//	lv_obj_set_style(lv_scr_act(), &style_date);
	date_label = lv_label_create(lv_scr_act(), NULL);
//	lv_label_set_style(date_label, LV_LABEL_STYLE_MAIN, &style_date);
	lv_label_set_text(date_label, "Mon 10 Jan");
	lv_obj_align(date_label, NULL, LV_ALIGN_CENTER, 0, 2);
	LOG_INF("Graphics init: Done");
}

void gfx_update(void)
{
	lv_task_handler();
}

void gfx_time_set_label(char *str)
{
	lv_label_set_text(time_label, str);
	lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void gfx_date_set_label(char *str)
{
	lv_label_set_text(date_label, str);
	lv_obj_align(date_label, NULL, LV_ALIGN_CENTER, 0, 8);
}

void gfx_bt_set_label(enum bt_symbol s)
{
	switch (s) {
	case BT_ADVERTISING_ON:
		lv_label_set_text(bt_label, LV_SYMBOL_WIFI);
		break;
	case BT_CONNECTED:
		lv_label_set_text(bt_label, LV_SYMBOL_BLUETOOTH);
		break;
	default:
		lv_label_set_text(bt_label, LV_SYMBOL_BLUETOOTH); //jj
		//lv_label_set_text(bt_label, "");
	}
}

void gfx_battery_set_label(enum battery_symbol s)
{
	switch (s) {
	case BAT_CHARGE:
		lv_label_set_text(battery_label, LV_SYMBOL_CHARGE);
		lv_obj_align(battery_label, NULL, LV_ALIGN_IN_TOP_RIGHT, -BAT_LABEL_MARGIN, BAT_LABEL_MARGIN);
		break;
	case BAT_FULL:
		lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_FULL);
		break;
	case BAT_3:
		lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_3);
		break;
	case BAT_2:
		lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_2);
		break;
	case BAT_1:
		lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_1);
		break;
	default:
		lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_EMPTY);
	}
	lv_obj_align(battery_label, NULL, LV_ALIGN_IN_TOP_RIGHT, -BAT_LABEL_MARGIN, 0);
}

void gfx_show_info(void)
{
	lv_obj_set_hidden(time_label, true);
	lv_obj_set_hidden(date_label, true);
	lv_obj_set_hidden(bt_label, true);
	lv_obj_set_hidden(info_label, false);
}

void gfx_show_watch(void)
{
	lv_obj_set_hidden(time_label, false);
	lv_obj_set_hidden(date_label, false);
	lv_obj_set_hidden(bt_label, false);
	lv_obj_set_hidden(info_label, true);
}
