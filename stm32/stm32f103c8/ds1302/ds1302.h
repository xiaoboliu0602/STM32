#ifndef __DS1302_H
#define __DS1302_H
#include "stm32f10x.h"

/*****************DS1302��������***************************************
*BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
* 0���ݲ���д�룬��ȡ����ʱ��Data
Addr4 Addr3 Addr2
Addr1 Addr0
д����
* 1����Ϊ1 ��ȡRAMʱ��Data������
**********************************************************************/

//�Ĵ�����ַ
typedef enum
{
DS1302_RdSec =           0x81, //BIT7: 0��������ģʽ; 1:�͹���ģʽ
DS1302_RdMin =           0x83,
DS1302_RdHour =          0x85, //BIT5: 0��12ʱ; 1��24ʱ
DS1302_RdDay =           0x87,
DS1302_RdMonth =         0x89,
DS1302_RdWeek =          0x8b,
DS1302_RdYear =          0x8d,
DS1302_RdProtect =       0x8f, //������
DS1302_RdTrickleCharge = 0x91,
DS1302_RdClockBurst    = 0xbf,
DS1302_WrSec =           0x80, //BIT7: 0��������ģʽ; 1:�͹���ģʽ
DS1302_WrMin =           0x82,
DS1302_WrHour =          0x84, //BIT5: 0��12ʱ; 1��24ʱ
DS1302_WrDay =           0x86,
DS1302_WrMonth =         0x88,
DS1302_WrWeek =          0x8a,
DS1302_WrYear =          0x8c,
DS1302_WrProtect =       0x8e, //д����
DS1302_WrTrickleCharge = 0x90,
}DS1302_RegAddr;

typedef enum
{
DS1302_WrClockBurst =    0xbe, //дʱ��ͻ��ģʽ
DS1302_RdRamBurst =      0xbf, //��ʱ��ͻ��ģʽ
DS1302_WrRAMBurst =      0xfe, //дRAMͻ��ģʽ
DS1302_RdRAMBurst=       0xff, //��RAMͻ��ģʽ
}DS1302_MODE;


//����ʱ��ṹ��
typedef struct
{
  u8 sec;
  u8 min;
  u8 hour;
  u8 day;
  u8 month;
  u8 year;
	u8 week;
}TIME_TypeDef;

//*****************DS1302��������*******************
//IO������
#define DS1302_PORT  GPIOD
#define DS1302_CLOCK RCC_APB2Periph_GPIOD

#define DS1302_SCK   GPIO_Pin_8   //DS1302_SCK
#define DS1302_DIO   GPIO_Pin_9   //DS1302_DIO
#define DS1302_CE    GPIO_Pin_10  //DS1302_CE

//�Ĵ���IO����״̬
#define Clr_Sclk() (GPIO_ResetBits(DS1302_PORT, DS1302_SCK))
#define Set_Sclk() (GPIO_SetBits(DS1302_PORT, DS1302_SCK))

#define Clr_Dio() (GPIO_ResetBits(DS1302_PORT, DS1302_DIO))
#define Set_Dio() (GPIO_SetBits(DS1302_PORT, DS1302_DIO))

#define Di_Ss() (GPIO_ResetBits(DS1302_PORT, DS1302_CE))
#define En_Ss() (GPIO_SetBits(DS1302_PORT, DS1302_CE))

#define Read_Dio() (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_DIO))

/*****************************��������*******************************/


/*****************************��������*******************************/
void DS1302_GPIO_Init(void);            //����STM32��GPIO��SPI�ӿ�
void DS1302_Write(void);                //����ʱ��   

void DS1302_WriteData(u8 addr,u8 data); //д��һ���ֽ�����
u8 DS1302_ReadByte(u8 addr);            //��ȡһ���ֽ�����

// ʹ�ã�
// DS1302_ReadByte(DS1302_RdHour);


#endif // __DS1302_H












