/*
 * settings.c
 *
 * Created: 5/25/2019
 * Author: efosmark
 */
#include "config.h"
#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdio.h>
#include "settings.h"
#include "drivers/vfd.h"
#include "drivers/pcf8523.h"

#include "display.h"

static uint8_t EEMEM temperatureUnit = TEMPERATURE_UNIT_CELSIUS;
static uint8_t EEMEM screenBrightness = VFD_BRIGHTNESS_100;
static uint8_t EEMEM localHoursOffset = 0;

char settings_get_temperature_unit() {
	char degrees = eeprom_read_byte(&temperatureUnit);
	if (degrees == 0xFF) degrees = TEMPERATURE_UNIT_CELSIUS;
	return degrees;
}

uint8_t settings_get_brightness() {
	char brightness = eeprom_read_byte(&screenBrightness);
	if (brightness == 0xFF) brightness = VFD_BRIGHTNESS_100;
	return brightness;
}

int8_t settings_get_hours_offset() {
	int8_t tzOffset = (int8_t) eeprom_read_byte(&localHoursOffset);
	if (tzOffset == 0xFF) tzOffset = 0;
	return tzOffset;
}

void settings_set_temperature_unit(char newTemperatureUnit) {
	eeprom_update_byte((uint8_t*) &temperatureUnit, (uint8_t) newTemperatureUnit);
}

void settings_set_brightness(uint8_t brightness) {
	eeprom_update_byte((uint8_t*) &screenBrightness, brightness);
	vfd_set_brightness(brightness);
}

void settings_set_hours_offset(int8_t tzOffset) {
	if (tzOffset == -12) tzOffset = 12;
	else if (tzOffset == 13) tzOffset = -12;
	eeprom_update_byte((uint8_t*) &localHoursOffset, (uint8_t) tzOffset);
}

void settings_set_minutes(int8_t minutes) {
	minutes = minutes % 60;
	PCF8523_setMinutes(minutes);
}

void settings_set_utc_hours(int8_t hours) {
	if (hours < 0) {
		hours += 24;
	}
	hours = hours % 24;
	PCF8523_setHours(hours);
}

char* settings_get_debug(char* str) {
	sprintf(str,
		"%02X %02X %02X",
		eeprom_read_byte(&temperatureUnit),
		eeprom_read_byte(&screenBrightness),
		eeprom_read_byte(&localHoursOffset)
	);
	return str;
}
