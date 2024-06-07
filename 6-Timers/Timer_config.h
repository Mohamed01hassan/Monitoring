/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : Timer                 ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*Choose waveform generation mode
 * 1-TIMER0_Normal
 * 2-TIMER0_PWM_PHASE_CORRECT
 * 3-TIMER0_COMPARE_MATCH
 * 4-TIMER0_FAST_PWM
 */
#define TIMER0_WAVEFORM_GEN_MODE		TIMER0_NORMAL


/*Choose CTC mode
 * 1-TIMER0_NORMAL_OPERATION
 * 2-TIMER0_TOGGLE_ON_COMPARE_MATCH
 * 3-TIMER0_CLEAR_ON_COMPARE_MATCH
 * 4-TIMER0_SET_ON_COMPARE_MATCH
 */
#define TIMER0_CTC_MODE				TIMER0_SET_ON_COMPARE_MATCH
#define COMPARE_MATCH_VALUE			64


/*Choose Fast PWM mode
 * 1-TIMER0_NORMAL_MODE
 * 2-TIMER0_RESERVED_MODE
 * 3-TIMER0_NON_INVERTING_MODE
 * 4-TIMER0_INVERTING_MODE
 */
#define TIMER0_FAST_PWM_MODE				TIMER0_NON_INVERTING_MODE


/*Choose TIMER0_Prescaler
 * 1-NO_PRESCALER
   2-PRESCALER_DIVIDED_BY_EIGHT
   3-PRESCALER_DIVIDED_BY_SIXTYFOUR
   4-PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX
   5-PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFO
 */
#define TIMER0_PRESCALER				PRESCALER_DIVIDED_BY_EIGHT


/*Choose waveform generation mode
 * 1-TIMER1_Normal
 * 2-TIMER1_PWM
 * 3-TIMER1_CTC
 * 4-TIMER1_FAST_PWM_ICR
 * 5-TIMER1_FAST_PWM_OCR
 */
#define TIMER1_WAVEFORM_GEN_MODE		TIMER1_FAST_PWM_ICR


/*Choose Compare match mode
 * 1-TIMER1_TOGGLE_ON_COMPARE_MATCH
 * 2-TIMER1_CLEAR_ON_COMPARE_MATCH
 * 3-TIMER1_SET_ON_COMPARE_MATCH
 */
#define TIMER1_COMPARE_MATCH_MODE		TIMER1_SET_ON_COMPARE_MATCH


/*Choose fast PWM mode
 * 1-TIMER1_NON_INVERTING_MODE
 * 2-TIMER1_INVERTING_MODE
 */
#define TIMER1_FAWT_PWM_MODE		TIMER1_NON_INVERTING_MODE

/*Choose TIMER0_Prescaler
 * 1-NO_PRESCALER
   2-PRESCALER_DIVIDED_BY_EIGHT
   3-PRESCALER_DIVIDED_BY_SIXTYFOUR
   4-PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX
   5-PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFO
 */
#define TIMER1_PRESCALER				PRESCALER_DIVIDED_BY_EIGHT

#endif
