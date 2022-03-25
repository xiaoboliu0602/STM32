/*********************** 2018_06_10 *********************
 *�ļ���  ��DS1302.c
 *����    ��ʱ��DS1302��������
 *��汾  ��ST3.5.0
 *˵��    ��DS1302����IOģ��SPI�ķ�ʽ
 *           LSB��ʽ������д���½���
 *********************************************************/
#include "ds1302.h"
#include "delay.h"

TIME_TypeDef time;

/**
 * @brief  ����GPIO��SPI�ӿڣ���������DS1302
 * @param  None
 * @retval DS1302_DIO����Ϊ��©ģʽ���Ա�ʵ��������˫��IO��
 */
//��ʼ��IO��
void DS1302_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_SCK|DS1302_DIO|DS1302_CE;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure); 
}

//��DS1302_DIO��Ϊ����
void Dio_In(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_DIO;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU;  //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

//��DS1302_DIO��Ϊ���
void  DIO_Out(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(DS1302_CLOCK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = DS1302_DIO;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(DS1302_PORT, &GPIO_InitStructure);
}

/**
* @brief  дһ��Byte��DS1302
* @param  dataΪҪд���Byte
* @retval дһ���ֽڵ����� SCK������д����
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
* @brief  ��DS1302SPI�����϶�ȡһ���ֽ�
* @param  addrΪ�Ĵ�����ַ
* @retval ��һ���ֽڵ����� SCK�½��ض�����
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
  Dio_In();   //������
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
* @brief  ��ָ���Ĵ���д��һ���ֽڵ�����
* @param  addrΪ�Ĵ�����ַ��dataΪд�������
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
* @brief  ��ʼ��ʱ��
* @param  
* @retval 
*/ 
void DS1302_Write(void)
{
	DS1302_WriteData(DS1302_WrProtect, 0x00); //��д����
	
	DS1302_WriteData(DS1302_WrSec, time.sec);
	DS1302_WriteData(DS1302_WrMin, time.min);
	DS1302_WriteData(DS1302_WrHour, time.hour);
	DS1302_WriteData(DS1302_WrDay, time.day);
	DS1302_WriteData(DS1302_WrMonth, time.month);
	DS1302_WriteData(DS1302_WrYear, time.year);
	DS1302_WriteData(DS1302_WrWeek, time.week);
	
	DS1302_WriteData(DS1302_WrProtect, 0x80); //��д����
}
