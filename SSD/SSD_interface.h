/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: HAL                 ********************/
/******************           SWC : SSD                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/




#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_ComAnode 		 	0
#define SSD_ComCathode  		1

#define ZERO       0
#define ONE        1
#define TWO        2
#define THREE      3
#define FOUR       4
#define FIVE       5
#define SIX        6
#define SEVEN      7
#define EIGHT      8
#define NINE       9

typedef struct
{
	u8 Copy_u8Port;
	u8 SSD_u8ComType:1;

}SSD_T;


u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_T* SSD);
u8 SSD_u8Enable(u8 Copy_u8Port, u8 Copy_u8Pin , u8 Copy_u8ComType);
u8 SSD_u8Disable(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8ComType);





#endif
