#ifndef __TIME_CYCCNT_H
#define __TIME_CYCCNT_H

#include "stm32f10x.h"

void CPU_TS_TmrInit(void); //初始化
uint32_t OS_TS_GET(void);  //获取计数器值


#endif // __TIME_CYCCNT_H
