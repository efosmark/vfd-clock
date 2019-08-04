/*
 * settings.h
 *
 * Created: 5/25/2019
 * Author: efosmark
 */
#ifndef SETTINGS_H_
#define SETTINGS_H_

#define EEPROM_ADDR_DEGREES 0x10
#define EEPROM_ADDR_BRIGHTNESS 0x11
#define EEPROM_ADDR_TZ_OFFSET 0x12
#define TEMPERATURE_UNIT_CELSIUS    'C'
#define TEMPERATURE_UNIT_FAHRENHEIT 'F'

char settings_get_temperature_unit();
uint8_t settings_get_brightness();
int8_t settings_get_hours_offset();

void settings_set_temperature_unit(char newTemperatureUnit);
void settings_set_brightness(uint8_t brightness);
void settings_set_minutes(int8_t minutes);
void settings_set_utc_hours(int8_t hours);
void settings_set_hours_offset(int8_t tzOffset);

char* settings_get_debug(char* str);

#endif /* SETTINGS_H_ */
