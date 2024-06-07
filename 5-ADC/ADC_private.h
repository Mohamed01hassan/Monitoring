/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : ADC                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define IDLE				0
#define BUSY				1

#define ENABLE				1
#define DISABLE				2

#define SINGLE_CHANNEL_ASYNCH		0
#define CHAIN_ASYNCH				1

#define AVCC				1
#define INTERNAL_VOLTAGE	2
#define AREF				3

#define ADMUX_MASK 			0b11100000
#define AUTO_TRIGGER_MASK 	0b00011111

#define SINGLE_CONVERSION	1
#define AUTO_TRIGGER		2

#define ADC_PRESCALER_MASK  0b11111000
#define DIV_BY_128			7
#define DIV_BY_64			6
#define DIV_BY_32			5
#define DIV_BY_16			4
#define DIV_BY_8			3
#define DIV_BY_4			2
#define DIV_BY_2			1

#define EIGHT_BITS		   	1
#define TEN_BITS			2

#define FREE_RUNNING			0
#define ANALOG_COMPARATOR		0b00100000
#define EXTERNAL_INTERRUPT		0b01000000
#define TIMER0_COMPARE_MATCH	0b01100000
#define TIMER0_OVERFLOW			0b10000000
#define TIMER1_COMPARE_MATCH	0b10100000
#define TIMER1_OVERFLOW			0b11000000
#define TIMER1_CAPTURE_EVENT	0b11100000



#endif

