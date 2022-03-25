#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"   /*ST库函数必备头文件*/
#include "usart1.h"	
#include "stdarg.h"

extern void DelayInit(void);    //记得初始化
extern void delay_ms(u16 nms);  //延时us
extern void delay_us(u32 nus);  //延时ms
extern void delay_s(u16 ns);    //延时s

extern void delay2(__IO u32 nCount);

#endif // __DELAY_H

