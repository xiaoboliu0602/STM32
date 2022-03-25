/*********************** 2018_06_10 *********************
 *文件名  ：DS1302.c
 *描述    ：时钟DS1302驱动程序
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *说明    ：DS1302采用IO模拟SPI的方式
 *           LSB格式，上升写，下降读
 *********************************************************/
#include "ds1302.h"
#include "delay.h"

TIME_TypeDef time;

/**
 * @brief  配置GPIO和SPI接口，用于连接DS1302
 * @param  None
 * @retval DS1302_DIO配置为开漏模式，以便实现真正的双向IO口
 */
//初始化IO口
void DS1302_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_SCK|DS1302_DIO|DS1302_CE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure); 
}

//将DS1302_DIO设为输入
void Dio_In(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_DIO;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;  //上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

//将DS1302_DIO设为输出
void  DIO_Out(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_DIO;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

/**
* @brief  写一个Byte到DS1302
* @param  data为要写入的Byte
* @retval 写一个字节的数据 SCK上升沿写数据
*/
void DS1302_WriteByte(u8 addr,u8 data)
{
  char  i=0;
  int Coda=0;
  Coda=(data<<8)|addr;
  En_Ss();
  for(i=0;i<16;i++)
  {  
    if((Coda&0x01)!=0)
      Set_Dio();
    else
      Clr_Dio();
    Set_Sclk();
    Coda=Coda>>1; 
    Clr_Sclk();
  }
  Di_Ss();
} 
 
/**
* @brief  从DS1302SPI总线上读取一个字节
* @param  addr为寄存器地址
* @retval 读一个字节的数据 SCK下降沿读数据
*/ 
u8 DS1302_ReadByte(u8 addr)
{
  char i,Coda;
  Coda=addr;
  En_Ss();
  for(i=0;i<8;i++)
  { 
    if((Coda&0x01)!=0)
      Set_Dio();
    else
      Clr_Dio();
    Set_Sclk();
    Coda=Coda>>1;
    Clr_Sclk();
  }
  Dio_In();   //读数据
  Coda=0;
  for(i=0;i<8;i++)
  {   
    if( Read_Dio()!=0)
      Coda|=(1<<i);
    Set_Sclk( );
    Clr_Sclk( );
  }
  Di_Ss();
  DIO_Out();              
  return Coda ;
}

/**
* @brief  向指定寄存器写入一个字节的数据
* @param  addr为寄存器地址，data为写入的数据
* @retval 
*/ 
void DS1302_WriteData(u8 addr,u8 data)
{
  Di_Ss();
  Clr_Sclk();
  delay_us(1);
  En_Ss();
  delay_us(2);
  DS1302_WriteByte(addr,data);
  Di_Ss();
  Clr_Sclk();
  delay_us(1);
}

/**
* @brief  初始化时间
* @param  
* @retval 
*/ 
void DS1302_Write(void)
{
	DS1302_WriteData(DS1302_WrProtect, 0x00); //关写保护
	
	DS1302_WriteData(DS1302_WrSec, time.sec);
	DS1302_WriteData(DS1302_WrMin, time.min);
	DS1302_WriteData(DS1302_WrHour, time.hour);
	DS1302_WriteData(DS1302_WrDay, time.day);
	DS1302_WriteData(DS1302_WrMonth, time.month);
	DS1302_WriteData(DS1302_WrYear, time.year);
	DS1302_WriteData(DS1302_WrWeek, time.week);
	
	DS1302_WriteData(DS1302_WrProtect, 0x80); //开写保护
}
