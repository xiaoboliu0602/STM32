/*********************** 2020_05_16 *********************
 *文件名  ：74HC595.c
 *描述    ：74HC595配置函数
 *硬件连接：DS、ST、SH
          
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/
 #include "HC595.h"
 
/*
 * 函数名：HC595_Config 
 * 描述  ：控制74HC595引脚配置
 * 输入  ：无
 * 输出  ：无
 */
void HC595_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN1|GPIO_PIN2|GPIO_PIN3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);

	GPIO_ResetBits(GPIO_PORT, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
}

/*
 * 函数名：HC595_SendData
 * 描述  ：写入HC595函数
 * 输入  ：待写入数据OutData
 * 输出  ：无
 */
void HC595_SendData(u8 OutData)
{
	unsigned char i; 
	for(i=0; i<8; i++) //将8位数据按位发送,先发送高字节后发送低字节
	{
			HC595_SH(RESET);//时钟线低电平
			if((OutData & 0x80) == 0x80)     //判断数据高低位
			{
				 HC595_DS(SET);                //数据线高电平
			}
			else
			{
				 HC595_DS(RESET);              //数据线低电平
			}
			OutData = OutData << 1;          //数据左移1位
			HC595_SH(SET);                   //时钟线高电平
	}
	//上升沿输出数据
	HC595_ST(RESET); 
	HC595_ST(SET);

}

/***************************END OF FILE**********************************/


