/******************************************************************************/
/******************************************************************************/
/******************     Name : Mohamed Hassan Mohamed    **********************/
/******************           Layer: HAL                 **********************/
/******************           SWC : CLCD                 **********************/
/******************           Version : 1.00             **********************/
/******************************************************************************/
/******************************************************************************/
#include "../4-LIB/STD_TYPES.h"
#include "../1-DIO/DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include <util/delay.h>



u8 CLCD_u8SendCommand(u8 Copy_u8Command)
{
	u8 Local_u8ErrorState=0;
	/*Set RS pin to low*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	/* Set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Send Command*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);

	/*Set high to E pin for 2 sec*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

	return Local_u8ErrorState;
}

u8 CLCD_u8SendData(u8 Copy_u8Data)
{
	u8 Local_u8ErrorState=0;



	/*Set RS pin to High for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/* Set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Send Data to Data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);

	/*Set high to E pin for 2 sec*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

	return Local_u8ErrorState;
}

u8 CLCD_u8SendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	u8 Local_u8ErrorState=0;

	while (Copy_pcString[Local_u8Counter] != '\0') // still looping until finishing all index of array
	{
		if (Local_u8Counter<16)
		{
			CLCD_u8SendData(Copy_pcString[Local_u8Counter]); // display string
			Local_u8Counter++;
		}
		else
		{
			CLCD_u8GoToXY(1,0);
			CLCD_u8SendData(Copy_pcString[Local_u8Counter]); // display string
			Local_u8Counter++;
		}
	}



	return Local_u8ErrorState;
}


u8 CLCD_u8GoToXY(u8 Copy_u8XPos ,u8 Copy_u8YPos)
{
	u8 Local_u8ErrorState=0;
	u8 Local_u8Address;

	if (Copy_u8XPos==0)
	{
		/*Location is at first line*/
		Local_u8Address=Copy_u8YPos;
	}
	else if (Copy_u8XPos==1)
	{
		/*Location is at second line*/
		Local_u8Address=Copy_u8YPos+0x40;
	}
	else Local_u8ErrorState=1;

	CLCD_u8SendCommand(Local_u8Address+128);

	return Local_u8ErrorState;
}

u8 CLCD_u8WriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8BlockNumber,u8 Copy_u8XPos ,u8 Copy_u8YPos)
{
	u8 Local_u8ErrorState=0;
	u8 Local_u8CGRAMAddress=0;
	u8 Local_u8Counter;
	Local_u8CGRAMAddress=Copy_u8BlockNumber*8; //Calculate CGRAM Address whose each block is 8 bytes

	CLCD_u8SendCommand(Local_u8CGRAMAddress+64);  // from datasheet send CGRAM Address to LCD with the sixth digit should be one

	for (Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_u8SendData(Copy_pu8Pattern[Local_u8Counter]);  // write the pattern into CGRAM
	}

	CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos); //Go back to DDRAM to display

	CLCD_u8SendData(Copy_u8BlockNumber);  //Display the pattern


	return Local_u8ErrorState;
}

void CLCD_voidShiftingStrLeft(char* Copy_pcString, u8 Copy_u8XPos , u8 Copy_u8YPos , u8 Copy_u8NumOfShiting )
{
	u8 Local_u8Iteration;
	for (Local_u8Iteration=0;Local_u8Iteration<=Copy_u8NumOfShiting;Local_u8Iteration++)
	{
		CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos-Local_u8Iteration);
		CLCD_u8SendString(&Copy_pcString);
		CLCD_u8SendCommand(0b00011000);		//To Shifting left
	}
}

void CLCD_voidShiftingStrRight(char* Copy_pcString, u8 Copy_u8XPos , u8 Copy_u8YPos , u8 Copy_u8NumOfShiting)
{
	u8 Local_u8Iteration;

	for (Local_u8Iteration=0;Local_u8Iteration<=Copy_u8NumOfShiting;Local_u8Iteration++)
	{
		CLCD_u8GoToXY(Copy_u8XPos,Copy_u8YPos+Local_u8Iteration);
		CLCD_u8SendString(&Copy_pcString);
		CLCD_u8SendCommand(0b00011100);		//To Shifting right

	}
}
void CLCD_voidWriteNumber(u32 Copy_u32Number)
{

	u8 Local_u8Counter1=0;
	u8 Local_u8Counter2;

	char NUM[15];		//Max No. of Characters in one row on LMB161A LCD

	while(Copy_u32Number != 0)
	{
		NUM[Local_u8Counter1]=Copy_u32Number % 10 ;  // To Get only Last digit
		Copy_u32Number/=10;   // new number is previous number without last digit
		Local_u8Counter1++;
	}

	u8 Local_u8ArrSize=Local_u8Counter1;  // To identify the size of  our Array

	for (Local_u8Counter2=Local_u8ArrSize;Local_u8Counter2>0;Local_u8Counter2--)
	{
		CLCD_u8SendData(NUM[Local_u8Counter2-1]+'0');  // To print The correct Number
	}

}


void CLCD_voidShiftingSpecialChar(u8* Copy_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos ,u8 Copy_u8YPos , u8 Copy_u8NumOfShiting ,u8 Copy_u8TypeOfShifting)
{
	u8 Local_u8Iteration;
	CLCD_u8WriteSpecialCharacter(Copy_pu8Pattern,Copy_u8BlockNum,Copy_u8XPos,Copy_u8YPos);
	if(Copy_u8TypeOfShifting==CLCD_SHIFTING_LEFT)

		for (Local_u8Iteration=0;Local_u8Iteration<=Copy_u8NumOfShiting;Local_u8Iteration++)
		{

			CLCD_u8SendCommand(0b00011000);		//To Shifting left
			_delay_ms(50);
		}
	else if (Copy_u8TypeOfShifting==CLCD_SHIFTING_RIGHT)
		for (Local_u8Iteration=0;Local_u8Iteration<=Copy_u8NumOfShiting;Local_u8Iteration++)
		{

			CLCD_u8SendCommand(0b00011100);		//To Shifting left
			_delay_ms(50);
		}

}

void CLCD_voidIntialization(void)
{
	/*wait for 40 ms*/
	_delay_ms(40);
	/*command func set*/
	CLCD_u8SendCommand(0b00111100);

	/*wait for 39 micro second
 we made delay already on the implementation of SendCommand func */

	/*display on off control : display enable,disable cursor & no blink cursor */
	CLCD_u8SendCommand(0b00001100);

	/*wait for 39 micro second
 we made delay already on the implementation of SendCommand func */

	/*Clear display*/
	CLCD_u8SendCommand(0b00000001);


}

