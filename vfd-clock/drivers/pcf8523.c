/*
 * pcf8523.c
 *
 * Created: 5/22/2019
 *  Author: efosmark
 */ 
#include "../config.h"
#include <util/delay.h>

#include "i2cmaster.h"
#include "pcf8523.h"

int8_t PCF8523_read(uint8_t pointer) {
	i2c_start_wait(PCF8523_I2C_ADDR+I2C_WRITE);
	i2c_write(pointer);
	i2c_stop();
	
	_delay_ms(10);
	i2c_start_wait(PCF8523_I2C_ADDR+I2C_READ);
	
	int8_t r2 = i2c_readNak();
	
	return r2;
}

void PCF8523_write(uint8_t pointer, uint8_t data) {
	i2c_start_wait(PCF8523_I2C_ADDR+I2C_WRITE);
	i2c_write(pointer);
	i2c_write(data);
	i2c_stop();
	
	_delay_ms(10);
}

int8_t PCF8523_getHours() {
	uint8_t raw = PCF8523_read(PCF8523_HOURS);
	int8_t tens = ((raw >> 4) * 10);
	int8_t ones = (raw & 0b1111);
	if (ones >= 10) {
		// Error state. Likely the first start up.
		PCF8523_setHours(0);
		PCF8523_setMinutes(0);
		tens = 0;
		ones = 0;
	}
	return tens + ones;
}

int8_t PCF8523_getMinutes() {
	uint8_t raw = PCF8523_read(PCF8523_MINUTES);
	return ((raw >> 4) * 10) + (raw & 0b1111);
}

int8_t PCF8523_getSeconds() {
	uint8_t raw = PCF8523_read(PCF8523_SECONDS);
	return (((raw >> 4) & 0b111) * 10) + (raw & 0b1111);
}

uint8_t PCF8523_isClockGuaranteed() {
	return PCF8523_read(PCF8523_SECONDS) >> 7;
}

void PCF8523_setHours(uint8_t hours) {
	uint8_t data = ((hours / 10) << 4) | (hours % 10);
	PCF8523_write(PCF8523_HOURS, data);
}

void PCF8523_setMinutes(uint8_t minutes) {
	uint8_t data = ((minutes / 10) << 4) | (minutes % 10);
	PCF8523_write(PCF8523_MINUTES, data);
}

void PCF8523_setSeconds(uint8_t seconds) {
	uint8_t data = ((seconds / 10) << 4) | (seconds % 10);
	PCF8523_write(PCF8523_SECONDS, data);
}
