#ifndef __USART1
#define __USART1

#include "stm32f10x.h"   /*ST�⺯���ر�ͷ�ļ�*/
#include "stdio.h"

void USART1_Config(void);
int fputc(int ch, FILE *f);
void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);


#endif // __USART1

