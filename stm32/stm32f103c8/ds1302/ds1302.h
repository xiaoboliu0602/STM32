#ifndef __DS1302_H
#define __DS1302_H
#include "stm32f10x.h"

/*****************DS1302控制命令***************************************
*BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
* 0数据不能写入，存取日历时钟Data
Addr4 Addr3 Addr2
Addr1 Addr0
写操作
* 1必须为1 存取RAM时钟Data读操作
**********************************************************************/

//寄存器地址
typedef enum
{
DS1302_RdSec =           0x81, //BIT7: 0正常工作模式; 1:低功耗模式
DS1302_RdMin =           0x83,
DS1302_RdHour =          0x85, //BIT5: 0：12时; 1：24时
DS1302_RdDay =           0x87,
DS1302_RdMonth =         0x89,
DS1302_RdWeek =          0x8b,
DS1302_RdYear =          0x8d,
DS1302_RdProtect =       0x8f, //读保护
DS1302_RdTrickleCharge = 0x91,
DS1302_RdClockBurst    = 0xbf,
DS1302_WrSec =           0x80, //BIT7: 0正常工作模式; 1:低功耗模式
DS1302_WrMin =           0x82,
DS1302_WrHour =          0x84, //BIT5: 0：12时; 1：24时
DS1302_WrDay =           0x86,
DS1302_WrMonth =         0x88,
DS1302_WrWeek =          0x8a,
DS1302_WrYear =          0x8c,
DS1302_WrProtect =       0x8e, //写保护
DS1302_WrTrickleCharge = 0x90,
}DS1302_RegAddr;

typedef enum
{
DS1302_WrClockBurst =    0xbe, //写时钟突发模式
DS1302_RdRamBurst =      0xbf, //读时钟突发模式
DS1302_WrRAMBurst =      0xfe, //写RAM突发模式
DS1302_RdRAMBurst=       0xff, //读RAM突发模式
}DS1302_MODE;


//定义时间结构体
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

//*****************DS1302控制命令*******************
//IO口配置
#define DS1302_PORT  GPIOD
#define DS1302_CLOCK RCC_APB2Periph_GPIOD

#define DS1302_SCK   GPIO_Pin_8   //DS1302_SCK
#define DS1302_DIO   GPIO_Pin_9   //DS1302_DIO
#define DS1302_CE    GPIO_Pin_10  //DS1302_CE

//寄存器IO操作状态
#define Clr_Sclk() (GPIO_ResetBits(DS1302_PORT, DS1302_SCK))
#define Set_Sclk() (GPIO_SetBits(DS1302_PORT, DS1302_SCK))

#define Clr_Dio() (GPIO_ResetBits(DS1302_PORT, DS1302_DIO))
#define Set_Dio() (GPIO_SetBits(DS1302_PORT, DS1302_DIO))

#define Di_Ss() (GPIO_ResetBits(DS1302_PORT, DS1302_CE))
#define En_Ss() (GPIO_SetBits(DS1302_PORT, DS1302_CE))

#define Read_Dio() (GPIO_ReadInputDataBit(DS1302_PORT, DS1302_DIO))

/*****************************变量定义*******************************/


/*****************************函数声明*******************************/
void DS1302_GPIO_Init(void);            //配置STM32的GPIO和SPI接口
void DS1302_Write(void);                //设置时间   

void DS1302_WriteData(u8 addr,u8 data); //写入一个字节数据
u8 DS1302_ReadByte(u8 addr);            //读取一个字节数据

// 使用：
// DS1302_ReadByte(DS1302_RdHour);


#endif // __DS1302_H












