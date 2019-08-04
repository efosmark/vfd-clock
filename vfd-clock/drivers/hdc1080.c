/*
 * hdc1080.h
 *
 * Created: 5/21/2019
 * Author: efosmark
 */ 
#include "../config.h"

#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>

#include "i2cmaster.h"
#include "hdc1080.h"

uint16_t HDC1080_read(uint8_t pointer) {
	i2c_start_wait(HDC1080_ADDR+I2C_WRITE);
	i2c_write(pointer);
	i2c_stop();
	
	_delay_ms(150);
	i2c_start_wait(HDC1080_ADDR+I2C_READ);
	
	uint16_t r1 = i2c_readAck();
	uint16_t r2 = i2c_readNak();
	
	return (r1 << 8) | r2;
}

void HDC1080_write(uint8_t pointer, uint8_t data) {
	i2c_start_wait(HDC1080_ADDR+I2C_WRITE);
	i2c_write(pointer);
	i2c_write(data);
	i2c_stop();
	
	_delay_ms(10);
}

double HDC1080_getTemperature() {
	uint16_t temperature = HDC1080_read(HDC1080_TEMPERATURE);
	return ((temperature / 65536.0) * 165.0) - 40.0;
}

double HDC1080_getHumidity() {
	uint16_t humidity = HDC1080_read(HDC1080_HUMIDITY);
	return ((humidity / 65536.0) * 100.0);
}

uint16_t HDC1080_getConfiguration() {
	return HDC1080_read(HDC1080_CONFIGURATION);
}

void HDC1080_setConfiguration(uint8_t data) {
	// TODO: Not yet implemented
}

double getAverageTemperature() {
	static uint8_t counter = 0;
	static double temperatureHistory[HDC1080_AVG_SAMPLE_COUNT] = { 0 };
	static bool full = false;
	
	temperatureHistory[counter] = HDC1080_getTemperature();

	counter++;
	if (counter >= HDC1080_AVG_SAMPLE_COUNT) {
		full = true;
		counter = 0;
	}
	
	double sum = 0;
	uint8_t numElements = full ? HDC1080_AVG_SAMPLE_COUNT : counter;
	for(int i=0; i<numElements;i++) sum += temperatureHistory[i];
	
	return (sum / numElements);
}

double getAverageHumidity() {
	static uint8_t counter = 0;
	static double humidityHistory[HDC1080_AVG_SAMPLE_COUNT] = { 0 };
	static bool full = false;
	
	humidityHistory[counter] = HDC1080_getHumidity();
	
	counter++;
	if (counter >= HDC1080_AVG_SAMPLE_COUNT) {
		full = true;
		counter = 0;
	}
	
	double sum = 0;
	uint8_t numElements = full ? HDC1080_AVG_SAMPLE_COUNT : counter;
	for(int i=0; i<numElements;i++) sum += humidityHistory[i];
	
	return (sum / numElements);
}

double celsiusToFahrenheit(double celsius) {
	return ((celsius * 9)/5) + 32;
}
