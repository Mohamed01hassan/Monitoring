/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : Timer                 ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/

#include"../4-LIB/STD_TYPES.h"
#include"../4-LIB/BIT_MATH.h"

#include"Timer_config.h"
#include"Timer_interface.h"
#include"Timer_private.h"
#include"Timer_register.h"

static void (*Timer0_pvCallBack)(void)=NULL;
static void (*Timer1_pvCallBack)(void)=NULL;
static void (*ICU_pvCallBackFunc)(void)=NULL;

void Timer0_voidInit(void)
{
	/*Choose waveform generation*/
#if(TIMER0_WAVEFORM_GEN_MODE==TIMER0_NORMAL)
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

#elif(TIMER0_WAVEFORM_GEN_MODE==TIMER0_PWM_PHASE_CORRECT)
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);

#elif(TIMER0_WAVEFORM_GEN_MODE==TIMER0_COMPARE_MATCH)
	CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*Output Compare match interrupt flag*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

#elif(TIMER0_WAVEFORM_GEN_MODE==TIMER0_FAST_PWM)
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
#else
#error "wrong waveform"
#endif

#if(TIMER0_CTC_MODE==TIMER0_SET_ON_COMPARE_MATCH)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif(TIMER0_CTC_MODE==TIMER0_CLEAR_ON_COMPARE_MATCH)
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif(TIMER0_CTC_MODE==TIMER0_TOGGLE_ON_COMPARE_MATCH)
	SET_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

#else
#error "wrong CTC Mode"
#endif

	/*Fast PWM MODE*/
#if(TIMER0_FAST_PWM_MODE==TIMER0_NON_INVERTING_MODE)
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#elif(TIMER0_FAST_PWM_MODE==TIMER0_INVERTING_MODE)
	SET_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

#else
#error "wrong Fast PWM Mode"
#endif


#if(TIMER0_PRESCALER==NO_PRESCALER)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

#elif(TIMER0_PRESCALER==PRESCALER_DIVIDED_BY_EIGHT)
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

#elif(TIMER0_PRESCALER==PRESCALER_DIVIDED_BY_SIXTYFOUR)
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

#elif(TIMER0_PRESCALER==PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX)
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);

#elif(TIMER0_PRESCALER==PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFOUR)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);

#else
#error "wrong PRESCALER"
#endif

/*Set compare match value */
OCR0=COMPARE_MATCH_VALUE;

}

void Timer1_voidInit(void)
{
	/*compare match mode*/
#if(TIMER1_COMPARE_MATCH_MODE==TIMER1_SET_ON_COMPARE_MATCH)
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1A0);

#elif(TIMER1_COMPARE_MATCH_MODE==TIMER1_CLEAR_ON_COMPARE_MATCH)
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

#elif(TIMER1_COMPARE_MATCH_MODE==TIMER1_TOGGLE_ON_COMPARE_MATCH)
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

#else
#error "wrong CTC Mode"
#endif

#if(TIMER1_FAWT_PWM_MODE==TIMER1_NON_INVERTING_MODE)
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

#elif(TIMER1_FAWT_PWM_MODE==TIMER1_INVERTING_MODE)
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1A0);

#else
#error "wrong Fast PWM Mode"
#endif

	/*Wave form generation mode */
#if(TIMER1_WAVEFORM_GEN_MODE==TIMER1_FAST_PWM_ICR)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

#elif(TIMER1_WAVEFORM_GEN_MODE==TIMER1_NORMAL)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

#elif(TIMER1_WAVEFORM_GEN_MODE==TIMER1_CTC)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

#else
#error "wrong Waveform Gen. Mode"
#endif

	/*Set prescaler */
#if(TIMER1_PRESCALER==PRESCALER_DIVIDED_BY_EIGHT)
	TCCR1B &= TIMER1_PRESCALER_MASK;
	TCCR1B |= PRESCALER_DIVIDED_BY_EIGHT;

#elif(TIMER1_PRESCALER==PRESCALER_DIVIDED_BY_SIXTYFOUR)
	TCCR1B &= TIMER1_PRESCALER_MASK;
	TCCR1B |= PRESCALER_DIVIDED_BY_SIXTYFOUR;

#elif(TIMER1_PRESCALER==PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX)
	TCCR1B &= TIMER1_PRESCALER_MASK;
	TCCR1B |= PRESCALER_DIVIDED_BY_TWOHUNDREDFIFTYSIX;

#elif(TIMER1_PRESCALER==PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFOUR)
	TCCR1B &= TIMER1_PRESCALER_MASK;
	TCCR1B |= PRESCALER_DIVIDED_BY_ONETHOUSANDTWENTEFOUR;
#else
#error "wrong PRESCALER "
#endif
}

void ICU_voidICUInit(void)
{
	/*set trigger*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*Enable prepheral */
	SET_BIT(TIMSK,TIMSK_TICIE1);

}

u8 ICU_u8SetTriggerEdge(u8 Copy_u8Edge)
{
	u8 Local_u8ErrorState= OK;
	if (Copy_u8Edge== ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if (Copy_u8Edge== ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else Local_u8ErrorState=NOK;
	return Local_u8ErrorState;
}

u16 ICU_u16ReadInputCapture(void)
{
return ICR1;
}

u8 ICU_voidCallBack(void(*Copy_pvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc !=NULL)
	{
		ICU_pvCallBackFunc=Copy_pvCallBackFunc;
	}
	else Local_u8ErrorState=NULL_POINTER;
	return Local_u8ErrorState;
}

void ICU_voidEnable(void)
{
SET_BIT(TIMSK,TIMSK_TICIE1);
}
void ICU_voidDisable(void)
{
CLR_BIT(TIMSK,TIMSK_TICIE1);
}

void Timer1_voidSetTimer1Value(u16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}

u16 Timer1_u16ReadTimer1Value(void)
{
return TCNT1;
}

void Timer1_voidSetICR(u16 Copy_u16TopValue)
{
	ICR1=Copy_u16TopValue;
}

void Timer1_voidSetChannelACompareMatch(u16 Copy_u16CompareValue)
{
	OCR1A=Copy_u16CompareValue;
}

void Timer1_voidSetChannelBCompareMatch(u16 Copy_u16CompareValue)
{
	OCR1B=Copy_u16CompareValue;
}

u8 Timer0_u8SetCallBack(void(*Copy_pvCallBack)(void))
{
	u8 Local_u8ErrorState=OK;

	if (Copy_pvCallBack!=NULL)
	{
		Timer0_pvCallBack=Copy_pvCallBack;
	}
	else Local_u8ErrorState=NULL_POINTER;

	return Local_u8ErrorState;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if (Timer0_pvCallBack!=NULL)
	{
		Timer0_pvCallBack();
	}
}
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(ICU_pvCallBackFunc !=NULL)
	{
		ICU_pvCallBackFunc();
	}
}
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if (Timer1_pvCallBack!=NULL)
	{
		Timer1_pvCallBack();
	}
}

