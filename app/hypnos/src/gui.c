/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gfx.h"
#include "gui.h"
#include "clock.h"
#include "battery.h"
#include "bt.h"
#include "log.h"

//static enum screen sc;

int gui_handle_button_event(void)
{
	clock_increment_local_time();
	clock_show_time();
	battery_show_status();
	gfx_update();

	return 1;
}
