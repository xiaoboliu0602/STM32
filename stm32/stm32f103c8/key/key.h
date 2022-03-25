#ifndef __LED_L
#define __LED_L

#include "stm32f10x.h"   /*ST库函数必备头文件*/

 #define RCC_KEY1        RCC_APB2Periph_GPIOA    // 时钟
 #define GPIO_KEY1_PORT  GPIOA                   // 管脚组号
 #define GPIO_KEY1       GPIO_Pin_0              // 管脚号
 
 #define NOKEY   0
 #define KEY1    1
 

  void Key_GPIO_Config(void);
	u8 ReadKeyDown(void);

#endif // __LED_L
