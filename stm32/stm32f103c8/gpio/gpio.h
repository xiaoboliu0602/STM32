#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"   /* ST库函数必备头文件 */

 #define ON  0
 #define OFF 1
 
 #define GPIO_PORT   GPIOB
 #define GPIO_PIN1   GPIO_Pin_0
 #define GPIO_PIN2   GPIO_Pin_5
 #define GPIO_PIN3   GPIO_Pin_1
 #define GPIO_CLK    RCC_APB2Periph_GPIOB
 

/* 带参数的宏 */
#define LED1(a) if (a)  \
                  GPIO_SetBits(GPIO_PORT, GPIO_PIN1);\
                else      \
                  GPIO_ResetBits(GPIO_PORT, GPIO_PIN1)
#define LED2(a) if (a)  \
                  GPIO_SetBits(GPIO_PORT, GPIO_PIN2);\
                else      \
                  GPIO_ResetBits(GPIO_PORT, GPIO_PIN2)
#define LED3(a) if (a)  \
                  GPIO_SetBits(GPIO_PORT, GPIO_PIN3);\
                else      \
                  GPIO_ResetBits(GPIO_PORT, GPIO_PIN3)

void GPIO_Config(void);


#endif // __GPIO_H



