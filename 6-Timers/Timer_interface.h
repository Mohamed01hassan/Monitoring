/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : Timer                 ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define ICU_RISING_EDGE			1
#define ICU_FALLING_EDGE		0

void Timer0_voidInit(void);

void Timer1_voidInit(void);

void Timer1_voidSetICR(u16 Copy_u16TopValue);

void Timer1_voidSetTimer1Value(u16 Copy_u16Value);

void TIMER1_voidSchedule(s32 Copy_s32Time_MicroSec,void (*Copy_pvFunc)(void), u8 Copy_u8Peiodicity);


void ICU_voidICUInit(void);

u8 ICU_u8SetTriggerEdge(u8 Copy_u8Edge);

void ICU_voidEnable(void);

void ICU_voidDisable(void);

u16 ICU_u16ReadInputCapture(void);


u8 ICU_voidCallBack(void(*Copy_pvCallBackFunc)(void));


u16 Timer1_u16ReadTimer1Value(void);

void Timer1_voidSetChannelACompareMatch(u16 Copy_u16CompareValue);

void Timer1_voidSetChannelBCompareMatch(u16 Copy_u16CompareValue);

u8 Timer0_u8SetCallBack(void(*Copy_pvCallBack)(void));

#endif
