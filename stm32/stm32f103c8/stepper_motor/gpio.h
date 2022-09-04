#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

 #define GPIO_PORT   GPIOB
 #define GPIO_PIN1   GPIO_Pin_5
 #define GPIO_PIN2   GPIO_Pin_6
 #define GPIO_PIN3   GPIO_Pin_7
 #define GPIO_PIN4   GPIO_Pin_8
 #define GPIO_CLK    RCC_APB2Periph_GPIOB

void GPIO_Config(void);

#endif // __GPIO_H
