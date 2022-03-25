/*********************** 2021_09_04 *********************
 *�ļ���  ��i2c.c
 *����    ��I2C ��������
 *��汾  ��ST3.5.0
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
   I2C_InitStructure.I2C_ClockSpeed = 100000;  /* 100K�ٶ� */
    
   I2C_Cmd(I2Cx, ENABLE);
   I2C_Init(I2Cx, &I2C_InitStructure);
   /*����1�ֽ�1Ӧ��ģʽ*/
   I2C_AcknowledgeConfig(I2Cx, ENABLE);
}
 
static void I2C_delay(uint16_t cnt)
{
	while(cnt--);
}

// �ȴ���ȡI2C���߿���Ȩ �ж�æ״̬
// - I2Cx:I2C�Ĵ�����ַ
// - I2C_Addr:��������ַ

static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr)
{
  vu16 SR1_Tmp;
  do
  {   
    I2C_GenerateSTART(I2Cx, ENABLE); /*��ʼλ*/
    /*��SR1*/
    SR1_Tmp = I2C_ReadRegister(I2Cx, I2C_Register_SR1);
    /*������ַ(д)*/
		I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
		
	}while(!(I2C_ReadRegister(I2Cx, I2C_Register_SR1) & 0x0002));
		
		I2C_ClearFlag(I2Cx, I2C_FLAG_AF);
			
		I2C_GenerateSTOP(I2Cx, ENABLE);  /*ֹͣλ*/  
}

// ͨ��ָ��I2C�ӿڶ�ȡ����ֽ�����
// - I2Cx:I2C�Ĵ�����ַ
// - I2C_Addr:��������ַ
// - addr:Ԥ��ȡ�ֽڴ洢λ��
// - *buf:��ȡ���ݵĴ洢λ��
// - num:��ȡ�ֽ���

uint8_t I2C_Read(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num)
{
  if(num==0)
	return 1;
	
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
		
	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
		
	/* ������ʼλ */
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/
		
	/*����������ַ(д)*/
	I2C_Send7bitAddress(I2Cx,  I2C_Addr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*���͵�ַ*/
	I2C_SendData(I2Cx, addr);
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*�����ѷ���*/
		
	/*��ʼλ*/
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
	/*������*/
	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	while (num)
	{
		if(num==1)
		{
			I2C_AcknowledgeConfig(I2Cx, DISABLE);	/* ���һλ��Ҫ�ر�Ӧ��� */
			I2C_GenerateSTOP(I2Cx, ENABLE);			  /* ����ֹͣλ */
		}
			
		while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
			*buf = I2C_ReceiveData(I2Cx);
			buf++;
			/* Decrement the read bytes counter */
			num--;
	}
		
	/* �ٴ�����Ӧ��ģʽ */
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	return 0;
}	

// ͨ��ָ��I2C�ӿ�д��һ���ֽ�����
// - I2Cx:I2C�Ĵ�����ַ
// - I2C_Addr:��������ַ
// - addr:Ԥд���ֽڵ�ַ
// - value:д������

uint8_t I2C_WriteOneByte(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t value)
{
	/* ��ʼλ */
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));  

	/* ����������ַ(д)*/
	I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*���͵�ַ*/
	I2C_SendData(I2Cx, addr);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* дһ���ֽ�*/
	I2C_SendData(I2Cx, value); 
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* ֹͣλ*/
	I2C_GenerateSTOP(I2Cx, ENABLE);

	I2C_AcknowledgePolling(I2Cx,I2C_Addr);

	I2C_delay(1000);

	return 0;
}

// ͨ��ָ��I2C�ӿ�д�����ֽ�����
// - I2Cx:I2C�Ĵ�����ַ
// - I2C_Addr:��������ַ
// - addr:Ԥд���ֽڵ�ַ
// - *buf:Ԥд�����ݴ洢λ��
// - num:д���ֽ���

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
 
