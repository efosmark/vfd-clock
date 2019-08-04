#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 800000UL  // 8 MHz

#define BTN_DEBOUNCE 200
#define SCREEN_WIDTH 24
#define HALF_LEN 12


/* I2C CONFIG */

#define TWSR TWSR1
#define TWBR TWBR1
#define TWCR TWCR1
#define TWDR TWDR1


/* PIN CONFIG */

// Status LEDs

#define PIN_STAT1  PD2
#define PORT_STAT1 PORTD
#define DDR_STAT1  DDRD

#define PIN_STAT2  PD3
#define PORT_STAT2 PORTD
#define DDR_STAT2  DDRD

#define PIN_STAT3  PD4
#define PORT_STAT3 PORTD
#define DDR_STAT3  DDRD

// Button switches

#define PIN_SW1  PC5
#define PORT_SW1 PORTC
#define DDR_SW1  DDRC

#define PIN_SW2  PC4
#define PORT_SW2 PORTC
#define DDR_SW2  DDRC

#define PIN_SW3  PC3
#define PORT_SW3 PORTC
#define DDR_SW3  DDRC

#define SW1_PRESSED (PINC & _BV(PIN_SW1)) == 0
#define SW2_PRESSED (PINC & _BV(PIN_SW2)) == 0
#define SW3_PRESSED (PINC & _BV(PIN_SW3)) == 0

#endif /* CONFIG_H_ */
