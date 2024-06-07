/*****************************************************************************/
/*****************************************************************************/
/******************     Name : Mohamed Hassan Mohamed     ********************/
/******************           Layer: MCAL                 ********************/
/******************           SWC : ADC                   ********************/
/******************           Version : 1.00              ********************/
/*****************************************************************************/
/*****************************************************************************/


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef struct
{
u8 size;
u8* ChannelArr;
u16* ResArr;
void (*NotificationFunc)(void);
}chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel , u16* Copy_pu16Reading);

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel , u16* Copy_pu16Reading , void(*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainAsynch(chain_t* Copy_chain);

s32 ADC_s32Mapping(f32 Copy_s32InputMin , f32 Copy_s32InputMax , f32 Copy_s32OutputMin , f32 Copy_s32OutputMax , f32 Copy_s32Input);


#endif
