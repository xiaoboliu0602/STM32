/*********************** 2015_12_22 *********************
 *文件名  ：usart1.c
 *描述    ：void USART1_Config(void)    //串口配置
            int fputc(int ch, FILE *f)  //printf函数重定向
            void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...) //类似printf
 *硬件连接：
 *库版本  ：ST3.5.0、
 *作者    ：xiaoboliu
 *********************************************************/
#include "usart1.h"
#include "stdarg.h"
/*
**函数名：USART1_Config()
**作  用：1.使能串口1的时钟
          2.配置usart1的I/O
		      3.配置usart1的工作模式：波特率115200、8个数据位、
		        1个停止位、无硬件流控制；即115200 8-N-1
**调  用：外部调用
**作  者：xiaoboliu
*/

void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//USART_ClockInitTypeDef USART_ClockInitStructure;
	
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	/* USART1 GPIO config */
	/* Configure USART1 Tx(PA.09) as alternate function pushpull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx(PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1 mode config */
	//USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //禁止USART时钟
	//USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;           //时钟极性低
	//USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;         //第2个边沿捕获数据
	//USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出
	
	USART_InitStructure.USART_BaudRate = 115200 ;                      //波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       //一个帧的数据位，8 or 9
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            //停止位数目,1 or 0.5 or 2 or 1.5
	USART_InitStructure.USART_Parity = USART_Parity_No;               //配置奇偶校验位,No失能,Even偶模式,Odd奇模式
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //硬件控制流失能
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //接收使能，发送使能
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);                                        //使能USART1
}


/*
**函数名：fputc
**作  用：重定向c库函数printf到USART1
**调  用：外部调用
**作  者：xiaoboliu
*/	
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return (ch);
}


/*
**函数名：itoa
**描  述：将整形数据转换成字符串
**输  入：-radix = 10 表示10进制，其他结果为0
          -valu  要转换的整形数
          -buf 转换后的字符串
**输  出：无
**返  回：无
**调  用：被USART1——printf()调用
*/
static char *itoa(int value, char *string, int radix)
{
	int i, d;
	int flag = 0;
	char *ptr = string;
	
	/* This implementation only works for decima numbers. */
	if(radix != 10)
	{
		*ptr = 0;
		return string;
	}
	
	if(!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}
	
	/* if this is a negative value insert the minus sign. */
	if(value < 0)
	{
		*ptr++ = '-';
		/* Make the value positive. */
		value *= -1;
	}
	for(i = 10000; i > 0; i /= 10)
	{
		d = value / i;
		if(d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}
	/* Null terminate the string. */
	*ptr = 0;
	return string;
}


/*
**函数名：USART1_printf
**描  述：格式化输出，类似于C库中的printf，但这里没有用到C库
**输  入：-USARTx 串口通道，这里用到USART1
**        -Data   要发送到串口的内容的指针
**			  -...    其他参数
**输  出：无
**返  回：无
**调  用：外部调用
**典型应用：USART1_printf(USART1, "\r\n this is a demo \r\n");
            USART1_printf(USART1, "\r\n %d \r\n", i);
						USART1_printf(USART1, "\r\n %s \r\n", j);
*/

void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...)
{
	const char *s;
	int d;
	char buf[16];
	va_list ap;
	va_start(ap, Data);
		while(*Data != 0)     //判断是否到达字符串结束符
		{
			if(*Data == 0x5c)   //'\'
			{
				switch(*++Data)
				{
					case 'r':                       //回车符
						USART_SendData(USARTx, 0x0d);
					  Data ++;
					  break;
					case 'n':                       //换行符
						USART_SendData(USARTx, 0x0a);  
					  Data ++;
					  break;
					default:
						Data ++;
					  break;
				}
			}
			else if(*Data == '%')
			{
				switch(*++Data)
				{
					case 's':         //字符串
						s = va_arg(ap, const char *);
					for(; *s; s++)
					{
						USART_SendData(USARTx, *s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
					}
					Data++;
					break;
					
					case 'd':         //十进制
					d = va_arg(ap, int);
					itoa(d, buf, 10);
					for(s = buf; *s; s++)
					{
						USART_SendData(USARTx, *s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
					}
					Data++;
					break;
					
					default:
						Data++;
					break;
				}
			}
			else USART_SendData(USARTx, *Data++);
			while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		}
}



