/**
  ******************************************************************************
  * @file    spi.c 
  * @author  xiaobo
  * @version V3.5.0
  * @date    20191125
  * @brief   SPI Configuration
	           PA4-SPIx-NSS  
  *			     PA5-SPIx-SCK  
  *			     PA6-SPIx-MISO
  *			     PA7-SPIx-MOSI
  ******************************************************************************
	* @SPI Library function
	*          SPI_DeInit(SPI1)                         //将SPI1寄存器重设为缺省值
	*          SPI_Init                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	*          SPI_StructInit                           //把SPI_InitStruct中的每一个参数按缺省值填入
	*          SPI_Cmd(SPI1, ENABLE)                    //使能或者失能SPI外设
	*          SPI_ITConfig(SPI2,SPI_IT_TXE,ENABLE)     //使能或失能指定的SPI中断
	*          SPI_DMACmd(SPI2,SPI_DMAReq_Rx,ENABLE)    //使能或失能指定的DMA请求              
	*          SPI_SendData(SPI2, 0xA5)                 //通过外设SPIx发送一个数据
	*          SPI_ReceiveData(SPI2)                    //返回通过SPIx最近接收的数据
	*          SPI_DMALastTransferCmd                   //
	*          SPI_NSSInternalSoftwareConfig            //为选定的SPI软件配置内部NSS管脚
	*          SPI_SSOutputCmd                          //使能或失能指定的SPI SS管脚
	*          SPI_DataSizeConfig(SPI1,SPI_DataSize_8b) //设置选定的SPI数据大小
	*          SPI_TransmitCRC(SPI2)                    //使能或失能指定SPI的CRC传输
	*          SPI_CalculateCRC(SPI1,ENABLE)            //使能或失能指定SPI的CRC值计算
	*          SPI_GetCRC(SPI2,SPI_CRC_Tx)              //返回指定SPI的CRC值
	*          SPI_GetCRCPolynomial                     //返回指定SPI的CRC多项式寄存器值
	*          SPI_BiDirectionalLineConfig              //选择指定SPI在双向模式下的数据传输方向
	*          SPI_GetFlagStatus                        //检查指定的SPI标志位设置与否
	*          SPI_ClearFlag                            //消除SPIx的待处理标志位
	*          SPI_GetITStatus                          //检查指定的SPI中断发生与否 
	*          SPI_ClearITPendingBit                    //清除SPIx的中断待处理位
	
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                  //复用为SPI1引脚
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
	SPI_NSS_HIGH();              //取消选中SPI从机
	
	/* SPI_ADXL configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //主机模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;                  //发送接收16位帧格式
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //同步时钟空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //第二个跳变沿采集数据
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS信号由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //分频系数为
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //数据输出为MSB先行
	SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
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
	
	while(SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE) == RESET){};   //等待发送区空
	
	SPI_I2S_SendData(SPI_SPIx, (TxDate|0x80)<<8);                          //通过SPI_SPIx发送一个字节数据,因为使用SPI16位传输，所有对数据进行移位操作
					
	while (SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_RXNE) == RESET){}; //等待接收完两个字节数据
	
	val = SPI_I2S_ReceiveData(SPI_SPIx) & 0xff;                            //取低8位数据
	
  /* Chip Select high */
  SPI_NSS_HIGH();		
	
	return val;                                //返回SPI_SPIx最近接收到的数据
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
	
	while(SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE) == RESET){}  //等待发送区空
	
	SPI_I2S_SendData(SPI_SPIx, add<<8|val);       //通过SPI_SPIx发送写入地址与数据，高8位为地址，低8位为数据
		
	while (SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个字节数据
	
	SPI_I2S_ReceiveData(SPI_SPIx);
	
  /* Chip Select high */
  SPI_NSS_HIGH();	
}


/*Get the flag status

  SPI_FLAG_BSY         忙标志位
  SPI_FLAG_OVR         超出标志位
  SPI_FLAG_MODF        模式错位标志位
  SPI_FLAG_CRCERR CRC  错位标志位
  SPI_FLAG_TXE         发送缓存空标志位
  SPI_FLAG_RXNE        接收缓存非空标志位
*/
//SPI_I2S_GetFlagStatus(SPI_SPIx, SPI_I2S_FLAG_TXE);  //检查发送缓存空标志位

/********************************END OF FILE***********************************/


