/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: HAL                 ********************/
/******************           SWC : SSD                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/


#include"../4-LIB/STD_TYPES.h"
#include"../4-LIB/BIT_MATH.h"
#include"../1-DIO/DIO_interface.h"
#include"SSD_interface.h"
#include"SSD_private.h"
#include"SSD_config.h"

u8 sevenseg[10]={0b00111111 // zero
		,0b00000110 // one
		,0b01011011 // two
		,0b01001111 // three
		,0b01100110 // four
		,0b01101101 // five
		,0b01111101 // six
		,0b00000111 // seven
		,0b01111111 // eight
		,0b01100111 // nine
};





u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_T* SSD)
{
	u8 Local_u8ErrorValue=0 ;

	if(Copy_u8Number<=NINE)
	{
		if(SSD->SSD_u8ComType==SSD_ComCathode){
			switch(SSD->Copy_u8Port)
			{
			case DIO_u8PORTA:
				DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTA,sevenseg[Copy_u8Number]);
				break;

			case DIO_u8PORTB:
				DIO_u8SetPortDirection(DIO_u8PORTB,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTB,sevenseg[Copy_u8Number]);
				break;
			case DIO_u8PORTC:
				DIO_u8SetPortDirection(DIO_u8PORTC,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTC,sevenseg[Copy_u8Number]);
				break;
			case DIO_u8PORTD:
				DIO_u8SetPortDirection(DIO_u8PORTD,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTD,sevenseg[Copy_u8Number]);
				break;
			default:Local_u8ErrorValue=1;break;
			}
		}

		else if (SSD->SSD_u8ComType==SSD_ComAnode){
			switch(SSD->Copy_u8Port)
			{
			case DIO_u8PORTA:
				DIO_u8SetPortDirection(DIO_u8PORTA,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTA,sevenseg[~Copy_u8Number]);
				break;

			case DIO_u8PORTB:
				DIO_u8SetPortDirection(DIO_u8PORTB,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTB,sevenseg[~Copy_u8Number]);
				break;
			case DIO_u8PORTC:
				DIO_u8SetPortDirection(DIO_u8PORTC,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTC,sevenseg[~Copy_u8Number]);
				break;
			case DIO_u8PORTD:
				DIO_u8SetPortDirection(DIO_u8PORTD,DIO_u8PORT_OUTPUT);
				DIO_u8SetPortValue(DIO_u8PORTD,sevenseg[~Copy_u8Number]);
				break;
			default:Local_u8ErrorValue=1;break;
			}
		}
	}
	else Local_u8ErrorValue=1;




	return Local_u8ErrorValue;
}

u8 SSD_u8Enable(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8ComType)
{
	u8 Local_u8ErrorState=0;

	if (Copy_u8Pin<=DIO_u8PIN7)
	{
		if (Copy_u8ComType==SSD_ComCathode)
		{
			switch (Copy_u8Port)
			{
			case DIO_u8PORTA :
				DIO_u8SetPinDirection(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_LOW);
				break;

			case DIO_u8PORTB :
				DIO_u8SetPinDirection(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_LOW);
				break;

			case DIO_u8PORTC :
				DIO_u8SetPinDirection(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_LOW);
				break;

			case DIO_u8PORTD :
				DIO_u8SetPinDirection(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_LOW);
				break;
			default: Local_u8ErrorState=1;

			}
		}
		else if (Copy_u8ComType==SSD_ComAnode)
		{

			switch (Copy_u8Port)
			{
			case DIO_u8PORTA :
				DIO_u8SetPinDirection(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_HIGH);
				break;

			case DIO_u8PORTB :
				DIO_u8SetPinDirection(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_HIGH);
				break;

			case DIO_u8PORTC :
				DIO_u8SetPinDirection(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_HIGH);
				break;

			case DIO_u8PORTD :
				DIO_u8SetPinDirection(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_OUTPUT);
				DIO_u8SetPinValue(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_HIGH);
				break;
			default: Local_u8ErrorState=1;


			}
		}

		else Local_u8ErrorState=1;
	}
	else Local_u8ErrorState=1;


	return Local_u8ErrorState;
}








u8 SSD_u8Disable(u8 Copy_u8Port, u8 Copy_u8Pin, u8 COM_TYPE)
{
	u8 Local_u8ErrorState=0;
	if (Copy_u8Pin<=DIO_u8PIN7)
		{
			if (COM_TYPE==SSD_ComAnode)
			{
				switch (Copy_u8Port)
				{
				case DIO_u8PORTA :
					DIO_u8SetPinDirection(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_LOW);
					break;

				case DIO_u8PORTB :
					DIO_u8SetPinDirection(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_LOW);
					break;

				case DIO_u8PORTC :
					DIO_u8SetPinDirection(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_LOW);
					break;

				case DIO_u8PORTD :
					DIO_u8SetPinDirection(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_LOW);
					break;
				default: Local_u8ErrorState=1;

				}
			}
			else if (COM_TYPE==SSD_ComCathode)
			{

				switch (Copy_u8Port)
				{
				case DIO_u8PORTA :
					DIO_u8SetPinDirection(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTA,Copy_u8Pin,DIO_u8PIN_HIGH);
					break;

				case DIO_u8PORTB :
					DIO_u8SetPinDirection(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTB,Copy_u8Pin,DIO_u8PIN_HIGH);
					break;

				case DIO_u8PORTC :
					DIO_u8SetPinDirection(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTC,Copy_u8Pin,DIO_u8PIN_HIGH);
					break;

				case DIO_u8PORTD :
					DIO_u8SetPinDirection(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_OUTPUT);
					DIO_u8SetPinValue(DIO_u8PORTD,Copy_u8Pin,DIO_u8PIN_HIGH);
					break;
				default: Local_u8ErrorState=1;


				}
			}

			else Local_u8ErrorState=1;
		}
		else Local_u8ErrorState=1;


	return Local_u8ErrorState;
}


