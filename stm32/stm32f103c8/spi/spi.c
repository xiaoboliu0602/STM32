/**
  ******************************************************************************
  * @file    spi.c 
  * @version V3.5.0
  * @date    20191125
  * @brief   SPI Configuration
	           PA4-SPIx-NSS  
  *			     PA5-SPIx-SCK  
  *			     PA6-SPIx-MISO
  *			     PA7-SPIx-MOSI
  ******************************************************************************
	* @SPI Library function
	*          SPI_DeInit(SPI1)                         //��SPI1�Ĵ�������Ϊȱʡֵ
	*          SPI_Init                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	*          SPI_StructInit                           //��SPI_InitStruct�е�ÿһ��������ȱʡֵ����
	*          SPI_Cmd(SPI1, ENABLE)                    //ʹ�ܻ���ʧ��SPI����
	*          SPI_ITConfig(SPI2,SPI_IT_TXE,ENABLE)     //ʹ�ܻ�ʧ��ָ����SPI�ж�
	*          SPI_DMACmd(SPI2,SPI_DMAReq_Rx,ENABLE)    //ʹ�ܻ�ʧ��ָ����DMA����              
	*          SPI_SendData(SPI2, 0xA5)                 //ͨ������SPIx����һ������
	*          SPI_ReceiveData(SPI2)                    //����ͨ��SPIx������յ�����
	*          SPI_DMALastTransferCmd                   //
	*          SPI_NSSInternalSoftwareConfig            //Ϊѡ����SPI���������ڲ�NSS�ܽ�
	*          SPI_SSOutputCmd                          //ʹ�ܻ�ʧ��ָ����SPI SS�ܽ�
	*          SPI_DataSizeConfig(SPI1,SPI_DataSize_8b) //����ѡ����SPI���ݴ�С
	*          SPI_TransmitCRC(SPI2)                    //ʹ�ܻ�ʧ��ָ��SPI��CRC����
	*          SPI_CalculateCRC(SPI1,ENABLE)            //ʹ�ܻ�ʧ��ָ��SPI��CRCֵ����
	*          SPI_GetCRC(SPI2,SPI_CRC_Tx)              //����ָ��SPI��CRCֵ
	*          SPI_GetCRCPolynomial                     //����ָ��SPI��CRC����ʽ�Ĵ���ֵ
	*          SPI_BiDirectionalLineConfig              //ѡ��ָ��SPI��˫��ģʽ�µ����ݴ��䷽��
	*          SPI_GetFlagStatus                        //���ָ����SPI��־λ�������
	*          SPI_ClearFlag                            //����SPIx�Ĵ�������־λ
	*          SPI_GetITStatus                          //���ָ����SPI�жϷ������ 
	*          SPI_ClearITPendingBit                    //���SPIx���жϴ�����λ
	
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/**
  * @brief  Initializes the peripherals used by the SPIx driver.
  * @param  None
  * @retval None
  */
void SPIx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	/* Enable SPIx and GPIO clocks */
	RCC_APB2PeriphClockCmd(SPI_SCK_GPIO_CLK | SPI_MISO_GPIO_CLK | 
	                       SPI_MOSI_GPIO_CLK | SPI_NSS_GPIO_CLK , ENABLE);

	/* SPI_ADXL Periph clock enable */
	RCC_APB2PeriphClockCmd(SPI_CLKx, ENABLE);
 
	/* Configure SPI pins: SCK */
	GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                  //����ΪSPI1����
	GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

	/* Configure SPI pins: MISO */
	GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;                      //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

	/* Configure SPI pins: MOSI */
	GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;                      //
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

	/* Configure SPI pins: NSS */
	GPIO_InitStructure.GPIO_Pin = SPI_NSS_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStructure);
	
	/* Deselect the device */
	SPI_NSS_HIGH();              //ȡ��ѡ��SPI�ӻ�
	
	/* SPI_ADXL configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //����ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;                  //���ͽ���16λ֡��ʽ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //ͬ��ʱ�ӿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //�ڶ��������زɼ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS�ź�����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //��Ƶϵ��Ϊ
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //�������ΪMSB����
	SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRCֵ����Ķ���ʽ
	SPI_Init(SPI_SPIx, &SPI_InitStructure);
	
	/* Enable SPIx  */
	SPI_Cmd(SPI_SPIx, ENABLE);	
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte
  *         received from the SPI bus.
  * @param  None
  * @retval None
  */ 
u8 SPI_ReadByte(u8 TxDate)
{
	u8 val;
	
  /* Chip Select low */
  SPI_NSS_LOW();	
	
	while(SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE) == RESET){};   //�ȴ���������
	
	SPI_I2S_SendData(SPI_SPIx, (TxDate|0x80)<<8);                          //ͨ��SPI_SPIx����һ���ֽ�����,��Ϊʹ��SPI16λ���䣬���ж����ݽ�����λ����
					
	while (SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_RXNE) == RESET){}; //�ȴ������������ֽ�����
	
	val = SPI_I2S_ReceiveData(SPI_SPIx) & 0xff;                            //ȡ��8λ����
	
  /* Chip Select high */
  SPI_NSS_HIGH();		
	
	return val;                                //����SPI_SPIx������յ�������
}

/**
  * @brief  Send two byte (add and data) through the SPI interface
  * @param  None
  * @retval None
  */ 
void SPI_WriteByte(u8 add, u8 val)
{
  /* Chip Select low */
  SPI_NSS_LOW();	
	
	while(SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE) == RESET){}  //�ȴ���������
	
	SPI_I2S_SendData(SPI_SPIx, add<<8|val);       //ͨ��SPI_SPIx����д���ַ�����ݣ���8λΪ��ַ����8λΪ����
		
	while (SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ���ֽ�����
	
	SPI_I2S_ReceiveData(SPI_SPIx);
	
  /* Chip Select high */
  SPI_NSS_HIGH();	
}


/*Get the flag status

  SPI_FLAG_BSY         æ��־λ
  SPI_FLAG_OVR         ������־λ
  SPI_FLAG_MODF        ģʽ��λ��־λ
  SPI_FLAG_CRCERR CRC  ��λ��־λ
  SPI_FLAG_TXE         ���ͻ���ձ�־λ
  SPI_FLAG_RXNE        ���ջ���ǿձ�־λ
*/
//SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE);  //��鷢�ͻ���ձ�־λ

/********************************END OF FILE***********************************/


