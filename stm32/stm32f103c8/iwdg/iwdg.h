#ifndef _IWDG_H
#define _IWDG_H

#include "stm32f10x.h"   /*ST�⺯���ر�ͷ�ļ�*/

void IWDG_Init(uint8_t pre,uint16_t rlv);
void IWDG_FeedDog(void);

#endif

