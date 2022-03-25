/*********************** 2020_09_23 *********************
 *�ļ���  ��i2c.c
 *����    ��io��ģ��I2C���ú���
 *��汾  ��ST3.5.0
 *����    ��xiaoboliu
 *********************************************************/
#include "i2c.h"

void I2C_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/* Configure I2C pins: PB6->SCL and PB7->SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void I2C_delay(void)
{
	u16 i = 20;   // Լ1us
	while(i--);
}

static FunctionalState I2C_Start(void)
{
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(!SDA_read)return DISABLE;	/* SDA��Ϊ�͵�ƽ������æ,�˳� */
	SDA_L;
	I2C_delay();
	if(SDA_read) return DISABLE;	/* SDA��Ϊ�ߵ�ƽ�����߳���,�˳� */
	SDA_L;
	I2C_delay();
	return ENABLE;
}

static void I2C_Stop(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SDA_H;
	I2C_delay();
}

static void I2C_Ack(void)
{
	SCL_L;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

static void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay();
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}

static FunctionalState I2C_WaitAck(void) 	
{
	SCL_L;
	I2C_delay();
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
		SCL_L;
		return DISABLE;
	}
	SCL_L;
	return ENABLE;
}
// �Ӹ�λ����λ����һ���ֽ�
void I2C_SendByte(uint8_t SendByte)
{
	uint8_t i=8;
	while(i--)
	{
		SCL_L;
		I2C_delay();
		if(SendByte&0x80)
			SDA_H;
		else 
			SDA_L;   
		SendByte <<= 1;
		I2C_delay();
	  SCL_H;
		I2C_delay();
	}
	SCL_L;
}

// �Ӹ�λ����λ����һ���ֽ�
uint8_t I2C_ReceiveByte(void)  
{ 
	uint8_t i=8;
	uint8_t ReceiveByte=0;

	SDA_H;				
	while(i--)
	{
		ReceiveByte <<= 1;      
		SCL_L;
		I2C_delay();
		SCL_H;
		I2C_delay();	
		if(SDA_read)
		{
			ReceiveByte |= 0x01;
		}
	}
	SCL_L;
	return ReceiveByte;
}

FunctionalState I2C_WriteByte(uint8_t SendByte, uint8_t WriteAddress)
{		
	if(!I2C_Start())return DISABLE;
	I2C_SendByte(I2C_WRITE_ADDR);  // ���� дָ��
	if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
	I2C_SendByte(WriteAddress);    // ���� ��ַ
	I2C_WaitAck();
	I2C_SendByte(SendByte);        // ���� ����
	I2C_WaitAck();
	I2C_Stop();
	
	return ENABLE;
}

FunctionalState I2C_ReadByte(uint8_t* pBuffer, uint16_t length, uint8_t ReadAddress)
{
	if(!I2C_Start())return DISABLE;
	I2C_SendByte(I2C_WRITE_ADDR);  // ���� дָ��
	if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
	I2C_SendByte(ReadAddress);     // ���� ��ַ
	I2C_WaitAck();
	if(!I2C_Start())return DISABLE;
	I2C_SendByte(I2C_READ_ADDR);   // ���� ��ָ��
	if(!I2C_Start())return DISABLE;
	
	while(length)
	{
		*pBuffer = I2C_ReceiveByte();
		if(length == 1)
			I2C_NoAck();
		else I2C_Ack(); 
			pBuffer++;
		length--;
	}
	I2C_Stop();
	return ENABLE;
}

