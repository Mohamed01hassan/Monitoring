/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : Timer                 ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TIMER1_PRESCALER_MASK							0b11111000

#define NO_PRESCALER										1
#define PRESCALER_DIVIDED_BY_EIGHT							2
#define PRESCALER_DIVIDED_BY_SIXTYFOUR						3
#define PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX				4
#define PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFOUR			5


#define ONCE												0
#define	PERIODIC											1

#define TIMER0_NORMAL										0
#define TIMER0_PWM_PHASE_CORRECT							1
#define TIMER0_COMPARE_MATCH								2
#define TIMER0_FAST_PWM										3

 #define TIMER0_NORMAL_OPERATION 							0
 #define TIMER0_TOGGLE_ON_COMPARE_MATCH						1
 #define TIMER0_CLEAR_ON_COMPARE_MATCH						2
 #define TIMER0_SET_ON_COMPARE_MATCH						3

#define  TIMER0_NORMAL_MODE     						    0
#define  TIMER0_TIMER0_RESERVED_MODE        			    1
#define  TIMER0_NON_INVERTING_MODE     		 	 		    2
#define  TIMER0_INVERTING_MODE          	 		 	    3

#define  TIMER1_Normal           						    0
#define  TIMER1_PWM              							1
#define  TIMER1_CTC           							    2
#define  TIMER1_FAST_PWM_ICR      							3
#define  TIMER1_FAST_PWM_OCR    						    4

 #define  TIMER1_TOGGLE_ON_COMPARE_MATCH    			    0
 #define  TIMER1_CLEAR_ON_COMPARE_MATCH     			    1
 #define  TIMER1_SET_ON_COMPARE_MATCH        			    2

 #define TIMER1_NON_INVERTING_MODE      					0
 #define TIMER1_INVERTING_MODE          				    1

#endif
