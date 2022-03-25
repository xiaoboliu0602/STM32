/**
  ******************************************************************************
  * @file    matrix_keyboard.h 
  * @author  xiaoboliu
  * @version V3.5.0
  * @date    06-January-2016
  * @brief   matrix keyboard module block.
  ******************************************************************************
  */
	
#ifndef __Matrix_key_H__
#define __Matrix_key_H__

#include "stm32f10x.h"   

/* GPIO for row */
 #define GPIO_ROW_PORT  GPIOE      
 #define GPIO_ROW_1     GPIO_Pin_1
 #define GPIO_ROW_2     GPIO_Pin_2
 #define GPIO_ROW_3     GPIO_Pin_3
 
/* GPIO for column */
 #define GPIO_COL_PORT  GPIOE      
 #define GPIO_COL_1     GPIO_Pin_4
 #define GPIO_COL_2     GPIO_Pin_5
 #define GPIO_COL_3     GPIO_Pin_6

/* return key number */
 #define KEY_NUB_0      0
 #define KEY_NUB_1      1
 #define KEY_NUB_2      2
 #define KEY_NUB_3      3
 #define KEY_NUB_4      4
 #define KEY_NUB_5      5
 #define KEY_NUB_6      6
 #define KEY_NUB_7      7
 #define KEY_NUB_8      8
 #define KEY_NUB_9      9 
										
extern u8 MatKey_Num(void);

#endif // __Matrix_key_H__

/**
  ******************************************************************************
  * @file    matrix_keyboard.c 
  * @author  xiaoboliu
  * @version V3.5.0
  * @date    06-January-2016
  * @brief   matrix keyboard module block.
  ******************************************************************************
  */
	
#include "matrix_keyboard.h" 

static void Delay(uint32_t n);

extern u8 MatKey_Num(void)
{
	GPIO_ResetBits(GPIO_ROW_PORT, GPIO_ROW_1);
	{
		if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
				return KEY_NUB_1;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
				return KEY_NUB_2;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
				return KEY_NUB_3;
		}
		else
			return KEY_NUB_0;
	}
	
	GPIO_ResetBits(GPIO_ROW_PORT, GPIO_ROW_2);
	{
		if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
				return KEY_NUB_4;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
				return KEY_NUB_5;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
				return KEY_NUB_6;
		}
		else
			return KEY_NUB_0;
	}
	
	GPIO_ResetBits(GPIO_ROW_PORT, GPIO_ROW_3);
	{
		if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_1))
				return KEY_NUB_7;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_2))
				return KEY_NUB_8;
		}
		else if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
		{
			Delay(20000); //20ms
			if(!GPIO_ReadInputDataBit(GPIO_COL_PORT, GPIO_COL_3))
				return KEY_NUB_9;
		}
		else
			  return KEY_NUB_0;
	}
	
}


/* 延时程序，已经实验测试，n微妙，误差<5% */
static void Delay(uint32_t n)              //n为延时时间微秒
{		SysTick -> LOAD = 24 * n;              //装载计数值
		SysTick -> CTRL = 0x00000005;          //时钟来源设为HCLK（72MHz），打开定时器
	  while(!(SysTick -> CTRL & 0x00010000));//等待计数到0
		SysTick -> CTRL = 0x00000004;          //关闭定时器
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ No.1 program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
  ******************************************************************************
  * @file    Delay.h 
  * @author  xiaoboliu
  * @version V3.5.0
  * @date    07-January-2016
  * @brief   Delay time module block.
  ******************************************************************************
  */

#ifndef __Matrix_key_H__
#define __Matrix_key_H__

#include "stm32f10x.h"   

exern void Delay(uint32_t n);

#endif // __Matrix_key_H__

/**
  ******************************************************************************
  * @file    Delay.c 
  * @author  xiaoboliu
  * @version V3.5.0
  * @date    07-January-2016
  * @brief   Delay time module block.
  ******************************************************************************
  */

#include "Delay.h"

/* 延时程序，已经实验测试，n微妙，误差<5% */
extern void Delay(uint32_t n)               //n为延时时间微秒
{		SysTick -> LOAD = 24 * n;              //装载计数值
		SysTick -> CTRL = 0x00000005;          //时钟来源设为HCLK（72MHz），打开定时器
	  while(!(SysTick -> CTRL & 0x00010000));//等待计数到0
		SysTick -> CTRL = 0x00000004;          //关闭定时器
}

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ No.2 program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~










