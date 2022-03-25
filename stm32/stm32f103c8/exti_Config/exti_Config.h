#ifndef __EXTI
#define __EXTI

#include "stm32f10x.h"   /*ST库函数必备头文件*/

//外部中断引脚定义PB13
/*
#define PX_INT_GPIO_PORT         GPIOB
#define PX_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PX_INT_GPIO_PIN          GPIO_Pin_13
#define PX_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define PX_INT_EXTI_PINSOURCE    GPIO_PinSource13
#define PX_INT_EXTI_LINE         EXTI_Line13
#define PX_INT_EXTI_IRQ          EXTI15_10_IRQn

#define PX_IRQHandler            EXTI13_IRQHandler
*/
#define PX2_INT_GPIO_PORT        GPIOB
#define PX2_INT_GPIO_CLK         (RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO)
#define PX2_INT_GPIO_PIN         GPIO_Pin_15
#define PX2_INT_EXTI_PORTSOURCE  GPIO_PortSourceGPIOB
#define PX2_INT_EXTI_PINSOURCE   GPIO_PinSource15
#define PX2_INT_EXTI_LINE        EXTI_Line15
#define PX2_INT_EXTI_IRQ         EXTI15_10_IRQn

#define PX2_IRQHandler           EXTI15_10_IRQHandler

void EXTI_PX_Config(void);

#endif // __EXTI




