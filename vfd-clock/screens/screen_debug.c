#include "../config.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

#include "screen_debug.h"
#include "../display.h"
#include "../settings.h"

#include "../drivers/vfd.h"
#include "../drivers/pcf8523.h" //todo

void screen_debug() {
	display_message("Debug");
	
	char str[20];
	settings_get_debug(str);
	
	vfd_clear();
	vfd_set_cursor(VFD_CURSOR_LINE_1);
	vfd_print(str);
	
	vfd_set_cursor(VFD_CURSOR_LINE_2);
	char str2[20];
	sprintf(str2,
		"%02X %02X",
		PCF8523_read(PCF8523_CONTROL_3),
		PCF8523_isClockGuaranteed()
	);
	vfd_print(str2);
	
	while (!SW1_PRESSED && !SW2_PRESSED && !SW3_PRESSED) _delay_ms(100);
	_delay_ms(BTN_DEBOUNCE);
}