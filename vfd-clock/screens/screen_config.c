#include "../config.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

#include "screen_config.h"
#include "../display.h"
#include "../bits.h"
#include "../settings.h"

#include "../drivers/vfd.h"
#include "../drivers/pcf8523.h"

void screen_config_degrees(bool editMode) {
	display_quad3("Degrees");
	char temperatureUnit = settings_get_temperature_unit();
	if (temperatureUnit == TEMPERATURE_UNIT_FAHRENHEIT) {
		display_quad4("Fahrenheit");
		} else {
		display_quad4("Celsius");
	}
	if (editMode && (SW2_PRESSED || SW3_PRESSED)) {
		_delay_ms(BTN_DEBOUNCE);
		settings_set_temperature_unit(
		temperatureUnit == TEMPERATURE_UNIT_FAHRENHEIT
		? TEMPERATURE_UNIT_CELSIUS
		: TEMPERATURE_UNIT_FAHRENHEIT
		);
	}
}

void screen_config_tz_offset(bool editMode) {
	display_quad3("Local Hour");
	int8_t hours = PCF8523_getHours();
	
	int8_t offset = settings_get_hours_offset();
	int8_t localHours = (hours + offset) % 24;
	if (localHours < 0) localHours = 24 + localHours;
	
	char offsetStr[5];
	sprintf(offsetStr,"%02d", localHours);
	display_quad4(offsetStr);
	
	if (editMode) {
		if (SW2_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_hours_offset(offset + 1);
			} else if (SW3_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_hours_offset(offset - 1);
		}
	}
}

void screen_config_utc_hours(bool editMode) {
	display_quad3("UTC Hour");
	int8_t hours = PCF8523_getHours();
	
	char hoursStr[3];
	sprintf(hoursStr,"%02d", hours);
	display_quad4(hoursStr);
	
	if (editMode) {
		if (SW2_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_utc_hours(hours + 1);
			} else if (SW3_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_utc_hours(hours - 1);
		}
	}
}

void screen_config_set_minutes(bool editMode) {
	display_quad3("Minutes");
	
	uint8_t minutes = PCF8523_getMinutes();
	
	char minutesStr[3];
	sprintf(minutesStr,"%02d", minutes);
	display_quad4(minutesStr);
	
	if (editMode) {
		if (SW2_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_minutes(minutes + 1);
			} else if (SW3_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_minutes(minutes - 1);
		}
	}
}

void screen_config_set_brightness(bool editMode) {
	display_quad3("Brightness");
	uint8_t percent = 100;
	uint8_t nextValue = VFD_BRIGHTNESS_100;
	uint8_t previousValue = VFD_BRIGHTNESS_75;
	switch(settings_get_brightness()) {
		case VFD_BRIGHTNESS_75:
		percent = 75;
		nextValue = VFD_BRIGHTNESS_100;
		previousValue = VFD_BRIGHTNESS_50;
		break;
		case VFD_BRIGHTNESS_50:
		percent = 50;
		nextValue = VFD_BRIGHTNESS_75;
		previousValue = VFD_BRIGHTNESS_25;
		break;
		case VFD_BRIGHTNESS_25:
		percent = 25;
		nextValue = VFD_BRIGHTNESS_50;
		previousValue = VFD_BRIGHTNESS_25;
		break;
	}
	
	char brightnessStr[6];
	sprintf(brightnessStr, "%d%%", percent);
	display_quad4(brightnessStr);
	
	if (editMode) {
		if (SW2_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_brightness(nextValue);
		} else if (SW3_PRESSED) {
			_delay_ms(BTN_DEBOUNCE);
			settings_set_brightness(previousValue);
		}
	}
}

bool screen_config_exit(bool editMode) {
	display_quad3("Exit");
	display_quad4("");
	if (editMode) {
		display_message("Complete.");
		return false;
	}
	return true;
}

void screen_config_menu() {
	bool configScreen = true;
	bool editMode = false;
	int currentItem = CONFIG_OPT_SET_DEG_TYPE;
	
	display_message("Settings");
	
	while (configScreen) {
		display_quad1("[\x7F][\x7E][\x9D]");
		display_quad2(editMode ? "(editing)" : "");

		switch (currentItem) {
			case CONFIG_OPT_SET_DEG_TYPE:
			screen_config_degrees(editMode);
			break;
			
			case CONFIG_OPT_SET_TZ_OFFSET:
			screen_config_tz_offset(editMode);
			break;
			
			case CONFIG_OPT_SET_UTC_HOUR:
			screen_config_utc_hours(editMode);
			break;
			
			case CONFIG_OPT_SET_MINUTE:
			screen_config_set_minutes(editMode);
			break;
			
			case CONFIG_OPT_SET_BRIGHTNESS:
			screen_config_set_brightness(editMode);
			break;
			
			case CONFIG_OPT_EXIT:
			configScreen = screen_config_exit(editMode);
			break;
		}
		
		if (SW2_PRESSED && SW3_PRESSED) {
			display_message("Created by Evan Fosmark.");
		} else if (SW2_PRESSED && !editMode) { // Up one menu option
			_delay_ms(BTN_DEBOUNCE);
			currentItem++;
			if (currentItem > CONFIG_OPT_EXIT) {
				currentItem = 0;
			}
			continue;
		} else if (SW3_PRESSED  && !editMode) { // Down one menu option
			_delay_ms(BTN_DEBOUNCE);
			currentItem--;
			if (currentItem < 0) {
				currentItem = CONFIG_OPT_EXIT;
			}
			continue;
		} else if (SW1_PRESSED) { // Edit current menu option
			_delay_ms(BTN_DEBOUNCE);
			editMode = !editMode;
			continue;
		}
		_delay_ms(SCREEN_CONFIG_REFRESH_DELAY);
	}
}
