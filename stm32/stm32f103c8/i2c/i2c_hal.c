/*********************** 2021_09_04 *********************
 *文件名  ：i2c.c
 *描述    ：I2C 驱动函数
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/
 
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
 
 void I2C_Configuration(void)
{
   I2C_InitTypeDef  I2C_InitStructure;
   GPIO_InitTypeDef  GPIO_InitStructure; 

   RCC_APB1PeriphClockCmd(RCC_I2Cx,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_GPIOx | RCC_APB2Periph_AFIO , ENABLE);

   /* Configure I2C1 pins: PB6->SCL and PB7->SDA */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_x1 | GPIO_Pin_x2;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
   GPIO_Init(GPIOx, &GPIO_InitStructure);
	
   I2C_DeInit(I2Cx);
   I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
   I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
   I2C_InitStructure.I2C_OwnAddress1 = 0x30;
   I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
   I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
   I2C_InitStructure.I2C_ClockSpeed = 100000;  /* 100K速度 */
    
   I2C_Cmd(I2Cx, ENABLE);
   I2C_Init(I2Cx, &I2C_InitStructure);
   /*允许1字节1应答模式*/
   I2C_AcknowledgeConfig(I2Cx, ENABLE);
}
 
static void I2C_delay(uint16_t cnt)
{
	while(cnt--);
}

// 等待获取I2C总线控制权 判断忙状态
// - I2Cx:I2C寄存器基址
// - I2C_Addr:从器件地址

static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr)
{
  vu16 SR1_Tmp;
  do
  {   
    I2C_GenerateSTART(I2Cx, ENABLE); /*起始位*/
    /*读SR1*/
    SR1_Tmp = I2C_ReadRegister(I2Cx, I2C_Register_SR1);
    /*器件地址(写)*/
		I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
		
	}while(!(I2C_ReadRegister(I2Cx, I2C_Register_SR1) & 0x0002));
		
		I2C_ClearFlag(I2Cx, I2C_FLAG_AF);
			
		I2C_GenerateSTOP(I2Cx, ENABLE);  /*停止位*/  
}

// 通过指定I2C接口读取多个字节数据
// - I2Cx:I2C寄存器基址
// - I2C_Addr:从器件地址
// - addr:预读取字节存储位置
// - *buf:读取数据的存储位置
// - num:读取字节数

uint8_t I2C_Read(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
  if(num==0)
	return 1;
	
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
		
	/* 发送起始位 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/
		
	/*发送器件地址(写)*/
	I2C_Send7bitAddress(I2Cx,  I2C_Addr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*发送地址*/
	I2C_SendData(I2Cx, addr);
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/
		
	/*起始位*/
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
	/*器件读*/
	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	while (num)
	{
		if(num==1)
		{
			I2C_AcknowledgeConfig(I2Cx, DISABLE);	/* 最后一位后要关闭应答的 */
			I2C_GenerateSTOP(I2Cx, ENABLE);			  /* 发送停止位 */
		}
			
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
			*buf = I2C_ReceiveData(I2Cx);
			buf++;
			/* Decrement the read bytes counter */
			num--;
	}
		
	/* 再次允许应答模式 */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	return 0;
}	

// 通过指定I2C接口写入一个字节数据
// - I2Cx:I2C寄存器基址
// - I2C_Addr:从器件地址
// - addr:预写入字节地址
// - value:写入数据

uint8_t I2C_WriteOneByte(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{
	/* 起始位 */
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));  

	/* 发送器件地址(写)*/
	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*发送地址*/
	I2C_SendData(I2Cx, addr);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* 写一个字节*/
	I2C_SendData(I2Cx, value); 
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* 停止位*/
	I2C_GenerateSTOP(I2Cx, ENABLE);

	I2C_AcknowledgePolling(I2Cx,I2C_Addr);

	I2C_delay(1000);

	return 0;
}

// 通过指定I2C接口写入多个字节数据
// - I2Cx:I2C寄存器基址
// - I2C_Addr:从器件地址
// - addr:预写入字节地址
// - *buf:预写入数据存储位置
// - num:写入字节数

uint8_t I2C_Write(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
	uint8_t err=0;
	
	while(num--)
	{
		if(I2C_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++))
		{
			err++;
		}
	}
	if(err)
		return 1;
	else 
		return 0;	
}

/***************************END OF FILE**********************************/
 
