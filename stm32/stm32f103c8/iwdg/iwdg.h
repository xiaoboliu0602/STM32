#ifndef _IWDG_H
#define _IWDG_H

#include "stm32f10x.h"   /*ST库函数必备头文件*/

void IWDG_Init(uint8_t pre,uint16_t rlv);
void IWDG_FeedDog(void);

#endif

