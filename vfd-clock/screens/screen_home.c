#include "../config.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "screen_home.h"
#include "../display.h"
#include "../settings.h"

#include "../drivers/hdc1080.h"
#include "../drivers/pcf8523.h"

void screen_home() {
	uint8_t hours = PCF8523_getHours();
	uint8_t minutes = PCF8523_getMinutes();
	
	int8_t localHours = (hours + settings_get_hours_offset()) % 24;
	if (localHours < 0) localHours = 24 + localHours;
	
	char line[24];
	
	sprintf(line, "Local %02d:%02d", localHours, minutes);
	display_quad2(line);
	
	sprintf(line, "UTC %02d:%02d", hours, minutes);
	display_quad4(line);
	
	double temperature = getAverageTemperature();
	double humidity = getAverageHumidity();
	
	// Temperature compensation
	temperature = (temperature * 0.569) + 8;
	
	char unit = settings_get_temperature_unit();
	if (unit == TEMPERATURE_UNIT_FAHRENHEIT) {
		temperature = celsiusToFahrenheit(temperature);
	}
	
	sprintf(line, "%.1f \xDF%c", temperature, unit);
	display_quad1(line);
	
	sprintf(line, "%.1f %%RH", humidity);
	display_quad3(line);
}