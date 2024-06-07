/******************************************************************************/
/******************************************************************************/
/******************     Name : Mohamed Hassan Mohamed    **********************/
/******************           Layer: HAL                 **********************/
/******************           SWC : CLCD                 **********************/
/******************           Version : 1.00             **********************/
/******************************************************************************/
/******************************************************************************/


/*Preprocessor file guard*/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#define CLCD_SHIFTING_LEFT    	0
#define CLCD_SHIFTING_RIGHT    	1


u8 CLCD_u8SendCommand(u8 Copy_u8Command);

u8 CLCD_u8SendData(u8 Copy_u8Data);

u8 CLCD_u8SendString(const char* Copy_pcString);

u8 CLCD_u8GoToXY(u8 Copy_u8XPos ,u8 Copy_u8YPos);

u8 CLCD_u8WriteSpecialCharacter(u8* Copy_pu8Pattern, u8 Copy_u8BlockNumber,u8 Copy_u8XPos ,u8 Copy_u8YPos);

void CLCD_voidWriteNumber(u32 Copy_u32Number);




void CLCD_voidIntialization(void);






#endif
