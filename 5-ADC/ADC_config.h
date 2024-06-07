/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : ADC                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define ADC_u32TIMEOUT	50000
/* Set the reference voltage
 * choose : 1- AVCC (with external capacitor to eliminate the noise )
 * 			2- AREF (External voltage)
 * 			3- INTERNAL_VOLTAGE (with external capacitor to eliminate the noise)*/

#define ADC_VOLTAGE_REF			AVCC

/*Set the prescaler : the division factor between the XTAL frequency and the input
clock to the ADC
 * choose : 1- DIV_BY_128
 * 			2- DIV_BY_64
 * 			3- DIV_BY_32
 * 			4- DIV_BY_16
 * 			5- DIV_BY_8
 * 			6- DIV_BY_4
 * 			7- DIV_BY_2
 * */
#define ADC_PRESCALER			DIV_BY_128

#define ADC_MAX_VOLTAGE			5


/* ADC Resolution
 * choose : 1- EIGHT_BITS
 * 			2- TEN_BITS
 */
#define ADC_RESOLURION			EIGHT_BITS

/*ADC Conversion Mode
 * choose : 1- SINGLE_CONVERSION
 * 			2- AUTO_TRIGGER*/
#define ADC_CONVERSION_MODE 	SINGLE_CONVERSION


/*ADC Auto trigger source (works only on Auto trigger mode)
 * choose : 1- FREE_RUNNING
 * 			2- ANALOG_COMPARATOR
 * 			3- EXTERNAL_INTERRUPT
 * 			4- TIMER0_COMPARE_MATCH
			5- TIMER0_OVERFLOW
			6- TIMER1_COMPARE_MATCH
			7- TIMER1_OVERFLOW
			8- TIMER1_CAPTURE_EVENT
 * 			*/
#define ADC_TRIGGER_SOURCE		FREE_RUNNING




#endif
