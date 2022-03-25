#ifndef __DS_18B20_H
#define __DS_18B20_H

#include "stm32f10x.h"
#include "delay.h"

/*ѡ��DQ��Ӧ�Ĺܽ�*/
#define DS18B20_DQ_OUT_PORT     GPIOB
#define DS18B20_DQ_OUT_CLK      RCC_APB2Periph_GPIOB

#define DS18B20_DQ_OUT_PIN      GPIO_Pin_11  // С��
#define Set_DS18B20_DQ_OUT      {GPIO_SetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN);} 
#define Clr_DS18B20_DQ_OUT      {GPIO_ResetBits(DS18B20_DQ_OUT_PORT,DS18B20_DQ_OUT_PIN);} 

#define DS18B20_DQ_IN_PORT      GPIOB
#define DS18B20_DQ_IN_CLK       RCC_APB2Periph_GPIOB
//#define DS18B20_DQ_IN_PIN       GPIO_Pin_1 // ���
#define DS18B20_DQ_IN_PIN       GPIO_Pin_11   // С��

/*��ȡһ���¶�ֵ*/
double DS18B20_data(void);  

#endif // __DS_18B20_H

