#include"4-LIB/STD_TYPES.h"
#include"4-LIB/BIT_MATH.h"

#include"5-ADC/ADC_interface.h"
#include"1-DIO/DIO_interface.h"
#include"2-PORT/PORT_interface.h"
#include"CLCD/CLCD_interface.h"
#include"4-GIE/GIE_interface.h"
#include"6-Timers/Timer_interface.h"
#include "KeyPad/KPD_interface.h"
#include "KeyPad/KPD_config.h"
#include "SSD/SSD_interface.h"
#include<util/delay.h>

f32 NUM(f32* Arr, u8 size);
u16 App_u16ADCReading1;
u16 App_u16ADCReading2;

void main ()
{



	SSD_T SSD1;
	SSD1.Copy_u8Port=DIO_u8PORTD;
	SSD1.SSD_u8ComType=SSD_ComCathode;

	f32 Local_IDArr[4];
	f32 Local_IDArrNUM;
	f32 Local_u8Password[4];
	f32 Local_u8CorrectPassword[4];
	f32 Local_u8PasswordNUM;
	f32 Local_u8CorrectPasswordNUM;
	u8 Local_u8Key;
	u16 MilliVolt;
	u16 Local_u16Temperature;
	s32 Local_u8NumberOfLeds;
	f32 Local_u8Leds;
	f32 Local_u16intensity;

	char welcome[]={"Welcome "};
	char ID[]={"Enter ID: "};
	char PASS[]={"Enter Pass: "};
	char Temp[]={"Temp: "};
	char Leds[]={"intensity:"};
	char TempUnit[]={"C"};
	char wrong[]={"WRONG"};

	PORT_voidInit();
	CLCD_voidIntialization();
	ADC_voidInit();

	GIE_voidEnable();


	u8 Local_u8Iterator1=0;
	u8 Local_u8Iterator2=0;
	u8 Local_u8ChancesIterator;
	//u8 Local_u8CheckIterator;
	u8 Local_u8CorrectCounter=1;



	CLCD_u8GoToXY(0,4);
	CLCD_u8SendString(welcome);
	_delay_ms(100);
	CLCD_u8SendCommand(1);
	CLCD_u8GoToXY(0,0);
	CLCD_u8SendString(ID);

	do
	{
		Local_u8Key=KPD_u8GetPressedKey();

		if (Local_u8Key>=0 && Local_u8Key<=9)
		{
			CLCD_voidWriteNumber(Local_u8Key);
			Local_IDArr[Local_u8Iterator1]=Local_u8Key;
			Local_u8Iterator1++;
		}


	}while(((Local_u8Key>=0 && Local_u8Key<=9)||(Local_u8Key==KPD_NO_PRESSED_KEY)) && (Local_u8Iterator1<4));


	Local_u8CorrectPassword[0]=Local_IDArr[3];
	Local_u8CorrectPassword[1]=Local_IDArr[2];
	Local_u8CorrectPassword[2]=Local_IDArr[1];
	Local_u8CorrectPassword[3]=Local_IDArr[0];

	Local_IDArrNUM=NUM(Local_IDArr,4);

	Local_u8CorrectPasswordNUM=NUM(Local_u8CorrectPassword,4);





	for(Local_u8ChancesIterator=5;Local_u8ChancesIterator>2;Local_u8ChancesIterator--)
	{
		CLCD_u8SendCommand(1);
		CLCD_u8SendString(PASS);

		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_LOW);
		SSD_u8SetNumber(Local_u8ChancesIterator-2,&SSD1);
		do
		{
			Local_u8Key=KPD_u8GetPressedKey();

			if (Local_u8Key>=0 && Local_u8Key<=9)
			{
				CLCD_voidWriteNumber(Local_u8Key);
				Local_u8Password[Local_u8Iterator2]=Local_u8Key;
				Local_u8Iterator2++;
			}

		}while(((Local_u8Key>=0 && Local_u8Key<=9)||(Local_u8Key==KPD_NO_PRESSED_KEY)) && (Local_u8Iterator2<4));

		Local_u8Iterator2=0;
		Local_u8PasswordNUM=NUM(Local_u8Password,4);

		if(Local_u8PasswordNUM==Local_u8CorrectPasswordNUM)
		{

			Local_u8ChancesIterator=1;
			Local_u8CorrectCounter=5;
		}
		else
		{
			//do nothing
		}

	}

	if(Local_u8CorrectCounter==5)
	{
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN5,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN6,DIO_u8PIN_LOW);
		CLCD_u8SendCommand(1);
		CLCD_u8SendString(welcome);
		CLCD_voidWriteNumber(Local_IDArrNUM);
		_delay_ms(100);
		CLCD_u8SendCommand(1);
		CLCD_u8SendString(Temp);
		CLCD_u8GoToXY(0,10);
		CLCD_u8SendData(0b11011111);
		CLCD_u8SendString(TempUnit);

		CLCD_u8GoToXY(1,0);
		CLCD_u8SendString(Leds);

		CLCD_u8GoToXY(1,14);
		CLCD_u8SendData(0b00100101);

		while(1)
		{
			ADC_u8StartConversionSynch(0,&App_u16ADCReading1);

			MilliVolt=(u16)((((u32)App_u16ADCReading1)*5000UL)/256UL);
			Local_u16Temperature=MilliVolt/10;
			CLCD_u8GoToXY(0,7);
			CLCD_voidWriteNumber(Local_u16Temperature);

			if(Local_u16Temperature>30)
			{
				DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_HIGH);
			}
			else
			{
				DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_LOW);
			}

			Timer1_voidInit();
			ADC_u8StartConversionSynch(1,&App_u16ADCReading2);
			Local_u8Leds=(u16)((((u32)App_u16ADCReading2)*5UL)/256UL);
			Local_u16intensity=20000-ADC_s32Mapping(0,5,0,20000,Local_u8Leds);
			Timer1_voidSetICR(20000);
			Timer1_voidSetChannelACompareMatch(Local_u16intensity);
			Local_u8NumberOfLeds=ADC_s32Mapping(0,20000,0,100,Local_u16intensity);
			CLCD_u8GoToXY(1,11);
			CLCD_voidWriteNumber(Local_u8NumberOfLeds);
			DIO_u8SetPortValue(DIO_u8PORTD,DIO_u8PORT_LOW);


		}

	}
}

f32 NUM(f32* Arr, u8 size)
{
	u8 Local_u8Iterator1;
	u8 Local_u8Iterator2;
	u8 Local_u8Iterator3;
	f32 Local_u8Num=0;
	for(Local_u8Iterator1=0;Local_u8Iterator1<size-1;Local_u8Iterator1++)
	{
		for (Local_u8Iterator2=1;Local_u8Iterator2<size-Local_u8Iterator1;Local_u8Iterator2++)
		{
			Arr[Local_u8Iterator1]=Arr[Local_u8Iterator1]*10;
		}
	}

	for (Local_u8Iterator3=0;Local_u8Iterator3<size;Local_u8Iterator3++)
	{

		Local_u8Num=Local_u8Num+Arr[Local_u8Iterator3];

	}
	return Local_u8Num;
}

