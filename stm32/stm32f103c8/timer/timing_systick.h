/**
  ******************************************************************************
  * @file    timing_systick.h
  * @author  xiaobo
  * @version V3.5.0
  * @date    20191217
  * @brief   Header for timing_systick.c module.
  ******************************************************************************
  */ 
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __TIMING_SYSTICK_H
#define __TIMING_SYSTICK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void SysTick_Init(void);
void timing_data(void);

#endif /* __TIMING_SYSTICK_H */

/********************************END OF FILE***********************************/

