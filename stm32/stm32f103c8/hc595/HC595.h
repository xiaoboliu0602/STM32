#ifndef __HC595_H
#define __HC595_H

#include "stm32f10x.h"

 #define RESET  0
 #define SET    1
 
 #define GPIO_PORT   GPIOB
 #define GPIO_PIN1   GPIO_Pin_5   // HC595_DS  串行数据输入
 #define GPIO_PIN2   GPIO_Pin_6   // HC595_ST  输入存储寄存器时钟
 #define GPIO_PIN3   GPIO_Pin_8   // HC595_SH  输入移位寄存器时钟
 #define GPIO_CLK    RCC_APB2Periph_GPIOB
 

#define HC595_DS(a) if (a)  \
                    GPIO_SetBits(GPIO_PORT, GPIO_PIN1);\
                    else      \
                    GPIO_ResetBits(GPIO_PORT, GPIO_PIN1)			
#define HC595_ST(a) if (a)  \
                    GPIO_SetBits(GPIO_PORT, GPIO_PIN2);\
                    else      \
                    GPIO_ResetBits(GPIO_PORT, GPIO_PIN2)		
#define HC595_SH(a) if (a)  \
                    GPIO_SetBits(GPIO_PORT, GPIO_PIN3);\
                    else      \
                    GPIO_ResetBits(GPIO_PORT, GPIO_PIN3)		
										
void HC595_Config(void);
void HC595_SendData(u8 OutData);

#endif // __HC595_H



