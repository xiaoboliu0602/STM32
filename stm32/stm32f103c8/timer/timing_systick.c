/**
  ******************************************************************************
  * @file    timing_systick.c
  * @version V3.5.0
  * @date    20191217
  * @brief   Systick configuration file.
  ******************************************************************************
  */ 
	
/* Includes ------------------------------------------------------------------*/
#include "timing_systick.h"	

/* Private typedef -----------------------------------------------------------*/
u32 timingdata = 0;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/	
/* Private function prototypes -----------------------------------------------*/	
	
/* Private functions ---------------------------------------------------------*/	
	
/**
  * @brief  SysTick_Init
  * @param  None
  * @retval None
  */	
void SysTick_Init(void)
{
  /* SystemCoreClock / 1000     1ms �ж�һ��
	 * SystemCoreClock / 100000  10us �ж�һ��
	 * SystemCoreClock / 1000000  1us �ж�һ��
	 */
	
	
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	/* AHB clock selected as SysTick clock source */
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
	if(SysTick_Config( SystemCoreClock / 1000)) 
	{
		while(1);
	}
	/* Disable SysTick counter */
	//SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	
	/* Enable SysTick counter */
	//SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	
}

/**
  * @brief  SysTick_Init
  * @param  None
  * @retval None
  */
void timing_data(void)
{
	timingdata ++;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*
void SysTick_Handler(void) // used in stm32f10x_it.c
{
	timing_data();
}
*/
/********************************END OF FILE***********************************/




