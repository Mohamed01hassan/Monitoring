/******************************************************************************/
/******************************************************************************/
/******************     Name : Mohamed Hassan Mohamed    **********************/
/******************           Layer: HAL                 **********************/
/******************           SWC : KEYPAD                 **********************/
/******************           Version : 1.00             **********************/
/******************************************************************************/
/******************************************************************************/


#include"../4-LIB/STD_TYPES.h"
#include"../4-LIB/BIT_MATH.h"

#include"../1-DIO/DIO_interface.h"
#include"KPD_interface.h"
#include"KPD_config.h"
#include"KPD_private.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8ColumnIndex;
	u8 Local_u8RowIndex;
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;
	u8 Local_u8PinState;
	static u8 Local_u8KPDColumnArr[NUM_OF_COLUMS]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8KPDRowArr[NUM_OF_ROWS]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};



	static u8 Local_u8KPDArr[NUM_OF_ROWS][NUM_OF_COLUMS]= KPD_ARR_VAL;

	for (Local_u8ColumnIndex=0;Local_u8ColumnIndex<NUM_OF_COLUMS;Local_u8ColumnIndex++)
	{

		/*Activation current column*/

		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIndex],DIO_u8PIN_LOW);
		for (Local_u8RowIndex=0;Local_u8RowIndex<NUM_OF_ROWS;Local_u8RowIndex++)
		{
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);

			if (DIO_u8PIN_LOW==Local_u8PinState)
			{

				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIndex][Local_u8ColumnIndex];
				/*Polling(busy waiting) until the key is released*/
				while(DIO_u8PIN_LOW==Local_u8PinState)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);

				}
					return Local_u8PressedKey;
			}

		}
		/*Deactivate current column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIndex],DIO_u8PIN_HIGH);
	}

	return Local_u8PressedKey;
}
