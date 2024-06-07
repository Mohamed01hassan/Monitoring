/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : Timer                 ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define	TCCR0				*((volatile u8*)0x53)		//Timer0 Control register
#define TCCR0_WGM00			6							//waveform generation mode bit0
#define TCCR0_COM01			5
#define TCCR0_COM00			4
#define TCCR0_WGM01			3							//waveform generation mode bit1
#define TCCR0_CS02			2							//prescaler bit2
#define TCCR0_CS01			1							//prescaler bit1
#define TCCR0_CS00			0							//prescaler bit0

#define	OCR0				*((volatile u8*)0x5C)		//Output compare register

#define TCCR1A				*((volatile u8*)0x4F)		//Timer1A Control register
#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0		6
#define TCCR1A_COM1B1		5
#define TCCR1A_COM1B0		4
#define TCCR1A_WGM11		1
#define TCCR1A_WGM10		0

#define TCNT1				*((volatile u16*)0x4C)		//Timer1 register

#define TCCR1B				*((volatile u8*)0x4E)		//Timer1B Control register
#define TCCR1B_CS10			0
#define TCCR1B_CS11			1
#define TCCR1B_CS12			2
#define TCCR1B_WGM12		3
#define TCCR1B_WGM13		4
#define TCCR1B_ICES1		6
#define TCCR1B_ICNC1		7

#define ICR1				*((volatile u16*)0x46)		//Timer1 Set Top Value

#define OCR1A				*((volatile u16*)0x4A)		//Timer1 Output compare register Channel A
#define OCR1B				*((volatile u16*)0x48)		//Timer1 Output compare register Channel B

#define	TIMSK				*((volatile u8*)0x59)		//Timer mask
#define	TIMSK_OCIE0			1							//Output compare 0 interrupt enable
#define	TIMSK_TICIE1		5
#endif
