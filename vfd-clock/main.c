/*
 * VFD clock project that runs an ATMega328PB to show time from a PCF8523,
 * and temperature + RH from a HDC1080.
 *
 * It expects a VFD of type CU24025ECPB-W1J, but can be configured for others
 * by editing drivers/vfd.h.
 *
 * Author: efosmark
 */
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>

#include "settings.h"
#include "bits.h"
#include "display.h"

#include "drivers/vfd.h"
#include "drivers/pcf8523.h"
#include "drivers/hdc1080.h"

#include "screens/screen_config.h"
#include "screens/screen_debug.h"
#include "screens/screen_home.h"

void init() {
	// Set to output
	bit_set(DDR_STAT1, PIN_STAT1);
	bit_set(DDR_STAT2, PIN_STAT2);
	bit_set(DDR_STAT3, PIN_STAT3);
	bit_set(PORT_STAT3, PIN_STAT3);
		
	// Set pull-up resistors
	bit_set(PORT_SW1, PIN_SW1);
	bit_set(PORT_SW2, PIN_SW2);
	bit_set(PORT_SW3, PIN_SW3);
	_delay_ms(1000);

	HDC1080_getTemperature(); // Try polling HDC1080
	bit_set(PORT_STAT1, PIN_STAT1);
	_delay_ms(500);
	
	PCF8523_write(PCF8523_CONTROL_3, 1 << 5); // Enable battery-backup
	bit_set(PORT_STAT2, PIN_STAT2);
	_delay_ms(500);
	
	vfd_init();
	display_message("Hello.");
	bit_set(PORT_STAT3, PIN_STAT3);
	_delay_ms(500);
	
	bit_clear(PORT_STAT1, PIN_STAT1);
	bit_clear(PORT_STAT2, PIN_STAT2);
	bit_clear(PORT_STAT3, PIN_STAT3);
}


int main(void) {
	init();
	
	unsigned char lastSecond = 0;
    for (;;) {
	    if (SW1_PRESSED) {
		    _delay_ms(BTN_DEBOUNCE);
		    screen_config_menu();
			continue;
		} else if (SW2_PRESSED && SW3_PRESSED) {
			screen_debug();
		}
		
	    unsigned char seconds = PCF8523_getSeconds();
		if (seconds != lastSecond) {
			lastSecond = seconds;
			screen_home();
		}
    }
}

