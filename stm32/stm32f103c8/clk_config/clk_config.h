#ifndef __CLK_CONFIG_H
#define	__CLK_CONFIG_H

#include "stm32f10x.h"

/**
  * ʹ��HSEʱ��SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16],�����128M
  * HSE_SetSysClock(RCC_PLLMul_9);
  */
void HSE_SetSysClock(uint32_t pllmul); 

/**
  * ʹ��HSIʱ��SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16],�����64MH
  * HSI_SetSysClock(RCC_PLLMul_16);
  */
void HSI_SetSysClock(uint32_t pllmul);

#endif /* __CLK_CONFIG_H */
