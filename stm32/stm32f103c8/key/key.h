#ifndef __LED_L
#define __LED_L

#include "stm32f10x.h"   /*ST�⺯���ر�ͷ�ļ�*/

 #define RCC_KEY1        RCC_APB2Periph_GPIOA    // ʱ��
 #define GPIO_KEY1_PORT  GPIOA                   // �ܽ����
 #define GPIO_KEY1       GPIO_Pin_0              // �ܽź�
 
 #define NOKEY   0
 #define KEY1    1
 

  void Key_GPIO_Config(void);
	u8 ReadKeyDown(void);

#endif // __LED_L
