/*
 * pcf8523.h
 *
 * Created: 5/22/2019
 *  Author: efosmark
 */ 
#ifndef PCF8523_H_
#define PCF8523_H_

#define PCF8523_I2C_ADDR 0xD0

// Control registers
#define PCF8523_CONTROL_1	0x00
#define PCF8523_CONTROL_2	0x01
#define PCF8523_CONTROL_3	0x02

// Time and date registers
#define PCF8523_SECONDS		0x03
#define PCF8523_MINUTES		0x04
#define PCF8523_HOURS		0x05
#define PCF8523_DAYS		0x06
#define PCF8523_WEEKDAYS	0x07
#define PCF8523_MONTHS		0x08
#define PCF8523_YEARS		0x09

// Alarm registers
#define PCF8523_MINUTE_ALARM	0x0A
#define PCF8523_HOUR_ALARM		0x0B
#define PCF8523_DAY_ALARM		0x0C
#define PCF8523_WEEKDAY_ALARM	0x0D

// Offset register
#define PCF8523_OFFSET	0x0E

// CLOCKOUT and timer registers
#define PCF8523_TMR_CLKOUT_CTRL	0x0F
#define PCF8523_TMR_A_FREQ_CTRL	0x10
#define PCF8523_TMR_A_REG		0x11
#define PCF8523_TMR_B_FREQ_CTRL	0x12
#define PCF8523_TMR_B_REG		0x13

int8_t PCF8523_read(uint8_t pointer);
void PCF8523_write(uint8_t pointer, uint8_t data);

int8_t PCF8523_getHours();
int8_t PCF8523_getMinutes();
int8_t PCF8523_getSeconds();
uint8_t PCF8523_isClockGuaranteed();

void PCF8523_setHours(uint8_t hours);
void PCF8523_setMinutes(uint8_t minutes);
void PCF8523_setSeconds(uint8_t seconds);

#endif /* PCF8523_H_ */
