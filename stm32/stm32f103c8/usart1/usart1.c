/*********************** 2015_12_22 *********************
 *�ļ���  ��usart1.c
 *����    ��void USART1_Config(void)    //��������
            int fputc(int ch, FILE *f)  //printf�����ض���
            void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...) //����printf
 *Ӳ�����ӣ�
 *��汾  ��ST3.5.0��
 *********************************************************/
#include "usart1.h"
#include "stdarg.h"
/*
**��������USART1_Config()
**��  �ã�1.ʹ�ܴ���1��ʱ��
          2.����usart1��I/O
		      3.����usart1�Ĺ���ģʽ��������115200��8������λ��
		        1��ֹͣλ����Ӳ�������ƣ���115200 8-N-1
**��  �ã��ⲿ����
**��  �ߣ�xiaoboliu
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx(PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* USART1 mode config */
	//USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     //��ֹUSARTʱ��
	//USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;           //ʱ�Ӽ��Ե�
	//USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;         //��2�����ز�������
	//USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable; //���һλ���ݵ�ʱ�����岻��SCLK���
	
	USART_InitStructure.USART_BaudRate = 115200 ;                      //����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;       //һ��֡������λ��8 or 9
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            //ֹͣλ��Ŀ,1 or 0.5 or 2 or 1.5
	USART_InitStructure.USART_Parity = USART_Parity_No;               //������żУ��λ,Noʧ��,Evenżģʽ,Odd��ģʽ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //Ӳ��������ʧ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //����ʹ�ܣ�����ʹ��
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);                                        //ʹ��USART1
}


/*
**��������fputc
**��  �ã��ض���c�⺯��printf��USART1
**��  �ã��ⲿ����
**��  �ߣ�xiaoboliu
*/	
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return (ch);
}


/*
**��������itoa
**��  ��������������ת�����ַ���
**��  �룺-radix = 10 ��ʾ10���ƣ��������Ϊ0
          -valu  Ҫת����������
          -buf ת������ַ���
**��  ������
**��  �أ���
**��  �ã���USART1����printf()����
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
**��������USART1_printf
**��  ������ʽ�������������C���е�printf��������û���õ�C��
**��  �룺-USARTx ����ͨ���������õ�USART1
**        -Data   Ҫ���͵����ڵ����ݵ�ָ��
**			  -...    ��������
**��  ������
**��  �أ���
**��  �ã��ⲿ����
**����Ӧ�ã�USART1_printf(USART1, "\r\n this is a demo \r\n");
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
		while(*Data != 0)     //�ж��Ƿ񵽴��ַ���������
		{
			if(*Data == 0x5c)   //'\'
			{
				switch(*++Data)
				{
					case 'r':                       //�س���
						USART_SendData(USARTx, 0x0d);
					  Data ++;
					  break;
					case 'n':                       //���з�
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
					case 's':         //�ַ���
						s = va_arg(ap, const char *);
					for(; *s; s++)
					{
						USART_SendData(USARTx, *s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
					}
					Data++;
					break;
					
					case 'd':         //ʮ����
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



