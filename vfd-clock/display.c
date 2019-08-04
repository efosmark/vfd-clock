/*
 * display.c - Simpler ways to write to specific parts of the screen.
 *
 * Created: 5/24/2019
 * Author: efosmark
 */
#include "config.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <avr/eeprom.h>

#include "display.h"
#include "bits.h"
#include "settings.h"

#include "drivers/vfd.h"
#include "drivers/hdc1080.h"
#include "drivers/pcf8523.h"

void display_message(const char* str) {
	vfd_clear();
	
	uint8_t padlen = (SCREEN_WIDTH - strlen(str)) / 2;
	vfd_set_cursor(VFD_CURSOR_LINE_1 + padlen);
	while (*str) {
		vfd_write(*str++, true);
		_delay_ms(10);
	}
	_delay_ms(500);
	vfd_clear();
}

void display_quad1(const char *str) {
	char quad[13];
	sprintf(quad, "%-12s", str);
	vfd_set_cursor(VFD_CURSOR_LINE_1);
	vfd_print(quad);
}

void display_quad2(const char *str) {
	char quad[13];
	sprintf(quad, "%12s", str);
	vfd_set_cursor(VFD_CURSOR_LINE_1 + HALF_LEN);
	vfd_print(quad);
}

void display_quad3(const char *str) {
	char quad[13];
	sprintf(quad, "%-12s", str);
	vfd_set_cursor(VFD_CURSOR_LINE_2);
	vfd_print(quad);
}

void display_quad4(const char *str) {
	char quad[13];
	sprintf(quad, "%12s", str);
	vfd_set_cursor(VFD_CURSOR_LINE_2 + HALF_LEN);
	vfd_print(quad);
}
