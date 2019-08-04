/*
 * vfd.h
 *
 * Created: 4/14/2019
 * Author: efosmark
 */ 
#ifndef VFD_H_
#define VFD_H_

#include <avr/io.h>
#include <stdbool.h>

#define PIN_RS   PD5  // 4
#define PORT_RS  PORTD
#define DDR_RS   DDRD

#define PIN_RW   PD7  // 5 (RW)
#define PORT_RW  PORTD
#define DDR_RW   DDRD

#define PIN_E    PD6  // 6 (E)
#define PORT_E   PORTD
#define DDR_E    DDRD

#define PIN_DB0  PB1  // 7
#define PORT_DB0 PORTB
#define DDR_DB0  DDRB

#define PIN_DB1  PB0  // 8
#define PORT_DB1 PORTB
#define DDR_DB1  DDRB

#define PIN_DB2  PE2  // 9
#define PORT_DB2 PORTE
#define DDR_DB2  DDRE

#define PIN_DB3  PB2  // 10
#define PORT_DB3 PORTB
#define DDR_DB3  DDRB

#define PIN_DB4  PC0  // 11
#define PORT_DB4 PORTC
#define DDR_DB4  DDRC

#define PIN_DB5  PE3  // 12
#define PORT_DB5 PORTE
#define DDR_DB5  DDRE

#define PIN_DB6  PC2  // 13
#define PORT_DB6 PORTC
#define DDR_DB6  DDRC

#define PIN_DB7  PC1  // 14
#define PORT_DB7 PORTC
#define DDR_DB7  DDRC


#define VFD_MIN_DELAY 10

#define VFD_FUNCTION_SET 0x38
#define VFD_CMD_CLEAR 0x01
#define VFD_CMD_CURSOR 0x80

#define VFD_BRIGHTNESS_100 0x00
#define VFD_BRIGHTNESS_75  0x01
#define VFD_BRIGHTNESS_50  0x02
#define VFD_BRIGHTNESS_25  0x03

#define VFD_CURSOR_LINE_1 0x00
#define VFD_CURSOR_LINE_2 0x40


void vfd_init();
void vfd_clear_data_pins();
void vfd_write(uint8_t data, bool rs);
void vfd_command(uint8_t data);
void vfd_clear();
void vfd_print(const char *str);
void vfd_set_cursor(uint8_t pos);
void vfd_blank(uint8_t num);
void vfd_set_brightness(uint8_t brightness);

#endif /* VFD_H_ */