/********************************************************************************
  * @file    clk_config.c 
  * @author  xiaoboliu
  * @version V3.5.0
  * @date    27-NOV-2019
  * @brief   HSE HSI Configuration 
	*
  * 程序来到main函数之前，启动文件：statup_stm32f10x_hd.s已经调用SystemInit()函数
	* 把系统时钟初始化成72MHZ
	*
	* SystemInit()在system_stm32f10x.c中定义
	*
	* 如果用户想修改系统时钟，可自行编写程序修改
	*
	* 重新设置系统时钟，这时候可以选择使用HSE还是HSI
	*
	* 使用HSE时，SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16],最高是128M
	* HSE_SetSysClock(RCC_PLLMul_9);
	*
	* 使用HSI时，SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16],最高是64MH
  * HSI_SetSysClock(RCC_PLLMul_16);
	
*******************************************************************************/
#include "clk_config.h"

/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源，和PLL的倍频因子，设置各种频率主要就是在这里设置
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * 设置 系统时钟:SYSCLK, AHB总线时钟:HCLK, APB2总线时钟:PCLK2, APB1总线时钟:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK/2,最高只能是36M
 * 参数说明：pllmul是PLL的倍频因子，在调用的时候可以是：RCC_PLLMul_x , x:[2,3,...16]
 * 举例：HSE_SetSysClock(RCC_PLLMul_9);  则设置系统时钟为：8MHZ * 9 = 72MHZ
 *       HSE_SetSysClock(RCC_PLLMul_16); 则设置系统时钟为：8MHZ * 16 = 128MHZ，超频慎用
 *
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 */
void HSE_SetSysClock(uint32_t pllmul)
{
	__IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

  RCC_DeInit();                              //RCC外设初始化成复位状态
  RCC_HSEConfig(RCC_HSE_ON);                 //使能HSE，开启外部晶振，通常是8M
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待HSE启动稳定
	
  if (HSEStartUpStatus == SUCCESS)           //如果HSE时间正常
  {
/*----------------------------------------------------------------------*/
		
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  //使能FLASH预存取缓冲区

    // SYSCLK周期与闪存访问时间的比例设置，这里统一设置成2
		// 设置成2，SYSCLK低于48M也可以工作
		// 设置成0、1，如果配置的SYSCLK超出了范围，则会导致硬件错误
		// 0：0 < SYSCLK <= 24M
		// 1：24< SYSCLK <= 48M
		// 2：48< SYSCLK <= 72M
    FLASH_SetLatency(FLASH_Latency_2);
		
/*----------------------------------------------------------------------*/
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1); // AHB 预分频因子设置为1分频，HCLK  = SYSCLK 
  
    RCC_PCLK2Config(RCC_HCLK_Div1);  // APB2预分频因子设置为1分频，PCLK2 = HCLK

    RCC_PCLK1Config(RCC_HCLK_Div2);  // APB1预分频因子设置为1分频，PCLK1 = HCLK/2 
		
/*-----------------设置各种频率主要就是在这里设置-------------------*/

    // 设置PLL时钟来源为HSE，设置PLL倍频因子
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul); // PLLCLK = 8MHz * pllmul
		
//------------------------------------------------------------------//

    RCC_PLLCmd(ENABLE);  // 开启PLL 

    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) // 等待 PLL稳定
    {
    }

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // 当PLL稳定之后，把PLL设置为系统时钟SYSCLK源

    while (RCC_GetSYSCLKSource() != 0x08)     // 读取时钟状态位，确保PLLCLK被选为系统时钟
    {
    }
  }
  else
  { 
		// 如果HSE开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
		// 当HSE开启失败或者故障的时候，单片机会自动把HSI设置为系统时钟，
		// HSI是内部的高速时钟，8MHZ
		
    while (1)
    {
    }
  }
}

/*
 * 使用HSI时，设置系统时钟的步骤
 * 1、开启HSI ，并等待 HSI 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源，和PLL的倍频因子，设置各种频率主要就是在这里设置
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/* 设置 系统时钟:SYSCLK, AHB总线时钟:HCLK, APB2总线时钟:PCLK2, APB1总线时钟:PCLK1
 * PCLK2 = HCLK = SYSCLK
 * PCLK1 = HCLK/2,最高只能是36M
 * 参数说明：pllmul是PLL的倍频因子，在调用的时候可以是：RCC_PLLMul_x , x:[2,3,...16]
 * 举例：HSI_SetSysClock(RCC_PLLMul_9);  则设置系统时钟为：4MHZ * 9 = 72MHZ
 *       HSI_SetSysClock(RCC_PLLMul_16); 则设置系统时钟为：4MHZ * 16 = 64MHZ
 *
 * HSI作为时钟来源，经过PLL倍频作为系统时钟，这是在HSE故障的时候才使用的方法
 * HSI会因为温度等原因会有漂移，不稳定，一般不会用HSI作为时钟来源，除非是迫不得已的情况
 * 如果HSI要作为PLL时钟的来源的话，必须二分频之后才可以，即HSI/2，而PLL倍频因子最大只能是16
 * 所以当使用HSI的时候，SYSCLK最大只能是4M*16=64M
 */
 
void HSI_SetSysClock(uint32_t pllmul)
{
	__IO uint32_t HSIStartUpStatus = 0;

  RCC_DeInit();                                // RCC外设初始化成复位状态

	RCC_HSICmd(ENABLE);                          // 使能HSI
	
	HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;  // 等待HSI就绪
	
  if (HSIStartUpStatus == RCC_CR_HSIRDY)     	 // HSI就绪之后则继续往下执行
  {
/*----------------------------------------------------------------------*/
    
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);   // 使能FLASH 预存取缓冲区

    // SYSCLK周期与闪存访问时间的比例设置，这里统一设置成2
		// 设置成2，SYSCLK低于48M也可以工作
	  // 如果设置成0、1，配置的SYSCLK超出了范围，则会导致硬件错误
		// 0：0 < SYSCLK <= 24M
		// 1：24< SYSCLK <= 48M
		// 2：48< SYSCLK <= 72M
    FLASH_SetLatency(FLASH_Latency_2);
		
/*----------------------------------------------------------------------*/
 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  // AHB 预分频因子设置为1分频，HCLK  = SYSCLK   
  
    RCC_PCLK2Config(RCC_HCLK_Div1);   // APB2预分频因子设置为1分频，PCLK2 = HCLK

    RCC_PCLK1Config(RCC_HCLK_Div2);   // APB1预分频因子设置为1分频，PCLK1 = HCLK/2 
		
//-----------------设置各种频率主要就是在这里设置-------------------//

    // 设置PLL时钟来源为HSE，设置PLL倍频因子
		// PLLCLK = 4MHz * pllmul
		
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
		
//------------------------------------------------------------------//

    RCC_PLLCmd(ENABLE);    // 开启PLL 

    
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  // 等待PLL稳定
    {
    }
    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  // 当PLL稳定之后，把PLL设置成系统时钟SYSCLK源

    
    while (RCC_GetSYSCLKSource() != 0x08) // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
    {
    }
  }
  else
  { 
		// 如果HSI开启失败，那么程序就会来到这里，用户可在这里添加出错的代码处理
		// 当HSE开启失败或者故障的时候，单片机会自动把HSI设置为系统时钟，
		// HSI是内部的高速时钟，8MHZ
		
    while (1)
    {
    }
  }
}
 
 







