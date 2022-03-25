#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"   /*ST�⺯���ر�ͷ�ļ�*/
#include "usart1.h"	
#include "stdarg.h"

extern void DelayInit(void);    //�ǵó�ʼ��
extern void delay_ms(u16 nms);  //��ʱus
extern void delay_us(u32 nus);  //��ʱms
extern void delay_s(u16 ns);    //��ʱs

extern void delay2(__IO u32 nCount);

#endif // __DELAY_H

