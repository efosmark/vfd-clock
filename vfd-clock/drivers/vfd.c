/*
 * vfd.c
 *
 * Created: 4/14/2019
 * Author: efosmark
 */ 
#include "../config.h"
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "../bits.h"
#include "../display.h"
#include "vfd.h"

void vfd_init() {
	// Raise
	bit_set(PORT_RS, PIN_RS);
	bit_set(PORT_E, PIN_E);
	bit_set(PORT_RW, PIN_RW);
		
	// Outputs
	bit_set(DDR_RS, PIN_RS);
	bit_set(DDR_RW, PIN_RW);
	bit_set(DDR_E, PIN_E);
	bit_set(DDR_DB0, PIN_DB0);
	bit_set(DDR_DB1, PIN_DB1);
	bit_set(DDR_DB2, PIN_DB2);
	bit_set(DDR_DB3, PIN_DB3);
	bit_set(DDR_DB4, PIN_DB4);
	bit_set(DDR_DB5, PIN_DB5);
	bit_set(DDR_DB6, PIN_DB6);
	bit_set(DDR_DB7, PIN_DB7);
		
	bit_set(DDRD, PD6);
	bit_set(PORTD, PD6);
		
	vfd_write(VFD_FUNCTION_SET, false);  // 8-bit function set
	vfd_write(VFD_FUNCTION_SET, false);  // 8-bit function set
	
	vfd_clear_data_pins();
		
	vfd_command(0x02);
	_delay_us(500);
}

void vfd_clear_data_pins() {
	bit_clear(PORT_DB0, PIN_DB0);
	bit_clear(PORT_DB1, PIN_DB1);
	bit_clear(PORT_DB2, PIN_DB2);
	bit_clear(PORT_DB3, PIN_DB3);
	bit_clear(PORT_DB4, PIN_DB4);
	bit_clear(PORT_DB5, PIN_DB5);
	bit_clear(PORT_DB6, PIN_DB6);
	bit_clear(PORT_DB7, PIN_DB7);
}

void vfd_write(uint8_t data, bool rs) {
	vfd_clear_data_pins();
	
	if(data & 0x01) { bit_set(PORT_DB0, PIN_DB0); }
	if(data & 0x02) { bit_set(PORT_DB1, PIN_DB1); }
	if(data & 0x04) { bit_set(PORT_DB2, PIN_DB2); }
	if(data & 0x08) { bit_set(PORT_DB3, PIN_DB3); }
	if(data & 0x10) { bit_set(PORT_DB4, PIN_DB4); }
	if(data & 0x20) { bit_set(PORT_DB5, PIN_DB5); }
	if(data & 0x40) { bit_set(PORT_DB6, PIN_DB6); }
	if(data & 0x80) { bit_set(PORT_DB7, PIN_DB7); }

	bit_clear(PORT_RW, PIN_RW);
	if (rs) bit_set(PORT_RS, PIN_RS); else bit_clear(PORT_RS, PIN_RS);
	bit_set(PORT_E, PIN_E);
	_delay_us(1);
	bit_clear(PORT_E, PIN_E);

	_delay_us(VFD_MIN_DELAY);
}

void vfd_command(uint8_t data) {
	vfd_write(data, false);
	_delay_us(VFD_MIN_DELAY);
}

void vfd_clear() {
	vfd_set_cursor(VFD_CURSOR_LINE_1);
	vfd_blank(SCREEN_WIDTH);
	vfd_set_cursor(VFD_CURSOR_LINE_2);
	vfd_blank(SCREEN_WIDTH);
}

void vfd_print(const char *str) {
	while (*str)
		vfd_write(*str++, true);
}

void vfd_set_cursor(uint8_t pos) {
	vfd_command(VFD_CMD_CURSOR|pos);
	_delay_us(VFD_MIN_DELAY);
}

void vfd_blank(uint8_t num) {
	while (num--) vfd_write(' ', true);
}

void vfd_set_brightness(uint8_t brightness) {
	vfd_write(VFD_FUNCTION_SET, false);
	vfd_write(brightness, true);
	_delay_us(VFD_MIN_DELAY);
}