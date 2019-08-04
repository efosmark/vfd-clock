/*
 * hdc1080.h
 *
 * Created: 5/21/2019
 * Author: efosmark
 */ 
#ifndef HDC1080_H_
#define HDC1080_H_

#define HDC1080_ADDR 0x80

#define HDC1080_TEMPERATURE 0x00
#define HDC1080_HUMIDITY 0x01
#define HDC1080_CONFIGURATION 0x02

#define HDC1080_AVG_SAMPLE_COUNT 20


uint16_t	HDC1080_getConfiguration();
double		HDC1080_getHumidity();
double		HDC1080_getTemperature();
uint16_t	HDC1080_read(uint8_t pointer);
void		HDC1080_setConfiguration(uint8_t data);
void		HDC1080_write(uint8_t pointer, uint8_t data);

// Helpers
double		getAverageTemperature();
double		getAverageHumidity();
double		celsiusToFahrenheit(double celsius);


#endif /* HDC1080_H_ */
