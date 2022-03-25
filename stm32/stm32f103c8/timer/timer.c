/*********************** 2021_04_19*********************
 *文件名  ：timer.c
 *描述    ：定时器
 *硬件连接：
 *库版本  ：ST3.5.0
 *作者    ：xiaobo
 *********************************************************/
#include "timer.h"
#include "led.h"
 
/*******************************************************************************
* Function Name  : TIM_Configuration
* Description    : TIM_Configuration program.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  TIM_DeInit(TIM2);
	
	/* 自动重装载寄存器周期的值(计数值),累计 TIM_Period个频率后产生一个更新或者中断 */
  TIM_TimeBaseStructure.TIM_Period = (10000 - 1);
	
	/* 时钟预分频数   例如：时钟频率=72MHZ/(时钟预分频+1) */
//  TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);	
	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
	
	/*
		使用计时器中断改变 IO 口电平，中断一次变化一次电平。
	
		当 TIM_Prescaler = (72 - 1) 时：
	
				TIM_Period					示波器实测频率   计时值
					2 - 1	  							 250kHz        2us
	        6 - 1					  		 83.34kHz        6us
	       10 -	1								 50.00kHz       10us
	       10                    45.45kHz				11us
				 25 - 1                20.00kHz       25us
	       25 									 19.24kHz       26us
			   50 - 1								 10.00kHz       50us
				 50	  								 9.804kHz			  51us
				100 - 1								 5.000kHz			 100us
				100		  							 4.950kHz      101us
				 
		所以：TIM_Period 的计数值应为 (n - 1), n为目标计时微秒值。
		注意：TIM_Period 不能为 0 ！！！
	*/
  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* 采样分频 */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/* 向上计数模式 */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             /* 初始化 TIMx 时间基数 */
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);				/* 清除溢出中断标志 */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    /* 开启定时器更新中断 */
  TIM_Cmd(TIM2, ENABLE);											/* 开启时钟 */
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configuration the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	      // 次
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 Handler.
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  static uint8_t display;
	
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) // 判断中断标志位
	{
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);      // 清除中断标志位
      
	    if( display ) 
		{ 
		  LED1(ON);
		}  
	    else 
		{ 
		  LED1(OFF);
		}
		display = ~display; 	 
  }	
}
