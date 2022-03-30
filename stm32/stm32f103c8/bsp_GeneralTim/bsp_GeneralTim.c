/**
  ******************************************************************************
  * @file    bsp_GeneralTim.c
  * @author  Bob
  * @version V3.5.0
  * @date    30-March-2022
  * @brief   Time base configuration
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#include "bsp_GeneralTim.h"

/* Input user value type */
TIM_ICUserValueTypeDef TIM_ICUserValueStructure = {0,0,0,0};

/* Configure the nested vectored interrupt controller. */
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the GENERAL_TIM_IRQ global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

static void GENERAL_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(GENERAL_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH3_PIN;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM_CH3_PORT, &GPIO_InitStructure);	
}


/*
* 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
* TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
* 另外三个成员是通用定时器和高级定时器才有.
*-----------------------------------------------------------------------------
*typedef struct
*{ TIM_Prescaler            都有
*  TIM_CounterMode			     TIMx,x[6,7]没有，其他都有
*  TIM_Period               都有
*  TIM_ClockDivision        TIMx,x[6,7]没有，其他都有
*  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]才有
*}TIM_TimeBaseInitTypeDef; 
*-----------------------------------------------------------------------------
*/

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;

  GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

  // 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
  TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;
  // 驱动CNT计数器的时钟 = Fck_int/(psc+1)
  TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

  /*--------------------输入捕获结构体初始化-------------------*/

  // 配置输入捕获的通道，需要根据具体的GPIO来配置
  TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_x;
  // 输入捕获信号的极性配置
  TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
  // 输入通道和捕获通道的映射关系，有直连和非直连两种
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  // 输入的需要被捕获的信号的分频系数
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  // 输入的需要被捕获的信号的滤波系数
  TIM_ICInitStructure.TIM_ICFilter = 0;
  // 定时器输入捕获初始化
  TIM_ICInit(GENERAL_TIM, &TIM_ICInitStructure);

  TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	

  //TIM_ITConfig (GENERAL_TIM, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
  TIM_ITConfig (GENERAL_TIM,  GENERAL_TIM_IT_CCx, ENABLE );

  TIM_Cmd(GENERAL_TIM, ENABLE);
}

void GENERAL_TIM_Init(void)
{
  GENERAL_TIM_GPIO_Config();
  GENERAL_TIM_NVIC_Config();
  GENERAL_TIM_Mode_Config();
}

/*********************************END OF FILE**********************************/
