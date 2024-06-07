/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : ADC                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/


#include"../4-LIB/STD_TYPES.h"
#include"../4-LIB/BIT_MATH.h"

#include"ADC_interface.h"
#include"ADC_register.h"
#include"ADC_private.h"
#include"ADC_config.h"

static u16* ADC_pu16Reading=NULL;
static void (*ADC_pvCallBackNotification)(void)=NULL;
u8 ADC_u8BusyState=IDLE;


static u8 ADC_u8ChainSize;  						//global variable to carry number of channels
static u8 ADC_u8ChainIndex=0;
static u8* ADC_pu8ChainChannelArr=NULL;		//global variable to carry channels array
static u16* ADC_pu16ChainResArr=NULL;		//global variable to carry result array

static u8 ADC_u8ISRSource;



void ADC_voidInit(void)
{

	//Check on Ref. Voltage
#if(ADC_VOLTAGE_REF==AVCC)
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif(ADC_VOLTAGE_REF==AREF)
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

#elif(ADC_VOLTAGE_REF==INTERNAL_VOLTAGE)
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error "wrong Voltage Reference configration option"
#endif
	/*Set prescaler */
	ADCSRA &= ADC_PRESCALER_MASK;
	ADCSRA |= ADC_PRESCALER;

	/*Left adjust or Right Adjust is Enable*/
#if (ADC_RESOLURION==EIGHT_BITS)
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif (ADC_RESOLURION==TEN_BITS)
	CLR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error "wrong Resolution configration option"
#endif

#if (ADC_CONVERSION_MODE==SINGLE_CONVERSION)
	CLR_BIT(ADCSRA,ADCSRA_ADATE);
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
#elif(ADC_CONVERSION_MODE==AUTO_TRIGGER)
	//Set Auto trigger Pin
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	//Set interrupt Enable
	SET_BIT(ADCSRA,ADCSRA_ADIE);
	//Set the trigger source
	SFIOR&=AUTO_TRIGGER_MASK;
	SFIOR|=ADC_TRIGGER_SOURCE;
	//Set the first Conversion
	SET_BIT(ADCSRA,ADCSRA_ADSC);

#else
#error "wrong ADC Conversion configration option"
#endif
	/*Enable peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel , u16* Copy_pu16Reading)
{
	u8 Local_u8ErrorState=OK;
	if (ADC_CONVERSION_MODE==SINGLE_CONVERSION)
	{
		if(ADC_u8BusyState==IDLE)
		{
			ADC_u8BusyState=BUSY;
			u32 Local_u32Counter=0;
			/*Clear The Mux bits in ADMUX register*/
			ADMUX &= ADMUX_MASK;

			/*Set the required channel into the Mux bits*/
			ADMUX |= Copy_u8Channel;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);


			/*busy waiting (polling) until the conversion complete flag is set or Counting reaches to Timeout value*/
			while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0) && Local_u32Counter < ADC_u32TIMEOUT)
			{
				Local_u32Counter++;
			}
			if (Local_u32Counter==ADC_u32TIMEOUT)
			{
				Local_u8ErrorState=NOK;
			}

			else
			{
				/*Clear the Flag*/
				SET_BIT(ADCSRA,ADCSRA_ADIF);
				// Return value
#if (ADC_RESOLURION==EIGHT_BITS)
					*Copy_pu16Reading=ADCH;
#elif (ADC_RESOLURION==TEN_BITS)
					*Copy_pu16Reading= ADC;
#endif

				ADC_u8BusyState=IDLE;
			}
		}
		else
		{
			Local_u8ErrorState=BUSY_FUNCTION;
		}
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{

		if (Copy_pvNotificationFunc==NULL || Copy_pu16Reading==NULL)
		{
			Local_u8ErrorState=NULL_POINTER;
		}
		else
		{
			ADC_u8ISRSource=SINGLE_CHANNEL_ASYNCH;
			ADC_u8BusyState=BUSY;
			/*Initialize the reading variables globally*/
			ADC_pu16Reading=Copy_pu16Reading;
			/*Initialize the callback notification function globally*/
			ADC_pvCallBackNotification=Copy_pvNotificationFunc;
			/*Clear The Mux bits in ADMUX register*/
			ADMUX &= ADMUX_MASK;

			/*Set the required channel into the Mux bits*/
			ADMUX |= Copy_u8Channel;

			SET_BIT(ADCSRA,ADCSRA_ADSC);

			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNCTION;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8StartChainAsynch(chain_t* Copy_chain)
{

	u8 Local_u8ErrorState =OK;
	if (Copy_chain == NULL_POINTER)
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	else
	{
		if(ADC_u8BusyState==IDLE)
		{
			ADC_u8ISRSource=CHAIN_ASYNCH;
			ADC_u8BusyState=BUSY_FUNCTION;

			ADC_pu16ChainResArr=Copy_chain->ResArr;
			ADC_pu8ChainChannelArr=Copy_chain->ChannelArr;
			ADC_u8ChainSize=Copy_chain->size;
			ADC_pvCallBackNotification=Copy_chain->NotificationFunc;

			/*Initialize current conversion index*/
			ADC_u8ChainIndex=0;

			/*set required channel*/
			ADMUX &= ADMUX_MASK;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable prephiral interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);

		}
		else
		{
			Local_u8ErrorState=BUSY_FUNCTION;
		}
	}
	return Local_u8ErrorState;
}

s32 ADC_s32Mapping(f32 Copy_s32InputMin , f32 Copy_s32InputMax , f32 Copy_s32OutputMin , f32 Copy_s32OutputMax , f32 Copy_s32Input)
{
	s32 Local_s32Output;

	Local_s32Output=(((Copy_s32OutputMax-Copy_s32OutputMin)/(Copy_s32InputMax-Copy_s32InputMin))*(Copy_s32Input-Copy_s32InputMin))+Copy_s32OutputMin;
	return Local_s32Output;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(ADC_u8ISRSource==SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC result*/
		*ADC_pu16Reading=ADCH;
		/* Return ADC idle again*/
		ADC_u8BusyState=IDLE;

		ADC_pvCallBackNotification();

		/*Disable ADC interrupt*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource==CHAIN_ASYNCH)
	{
		/*read current conversion*/
#if ADC_RESOLURION==EIGHT_BITS
		ADC_pu16ChainResArr[ADC_u8ChainIndex]=ADCH;
#elif ADC_RESOLURION==TEN_BITS
		ADC_pu16ChainResArr[ADC_u8ChainIndex]=ADC;
#endif

		/*increment index*/
		ADC_u8ChainIndex++;

		/*check chain is finished or not*/
		if (ADC_u8ChainIndex==ADC_u8ChainSize)
		{
			/*chain is finished*/

			/*Make ADC IDLE*/
			ADC_u8BusyState=IDLE;

			/*Invoke Call back notification function*/
			ADC_pvCallBackNotification();

			/*Disable interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}

		else
		{
			/*chain isn't finished*/

			/*Set new required channel*/
			ADMUX &= ADMUX_MASK;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ChainIndex];

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}


