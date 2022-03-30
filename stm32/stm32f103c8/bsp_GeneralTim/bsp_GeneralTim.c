/**
  ******************************************************************************
  * @file    bsp_GeneralTim.c
  * @author  Bob
  * @version V3.5.0
  * @date    30-March-2022
  * @brief   Time base configuration
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
* ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
* TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
* ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
*-----------------------------------------------------------------------------
*typedef struct
*{ TIM_Prescaler            ����
*  TIM_CounterMode			     TIMx,x[6,7]û�У���������
*  TIM_Period               ����
*  TIM_ClockDivision        TIMx,x[6,7]û�У���������
*  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
*}TIM_TimeBaseInitTypeDef; 
*-----------------------------------------------------------------------------
*/

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void GENERAL_TIM_Mode_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;

  GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

  // �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
  TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_PERIOD;
  // ����CNT��������ʱ�� = Fck_int/(psc+1)
  TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_PSC;
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

  /*--------------------���벶��ṹ���ʼ��-------------------*/

  // �������벶���ͨ������Ҫ���ݾ����GPIO������
  TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_x;
  // ���벶���źŵļ�������
  TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_STRAT_ICPolarity;
  // ����ͨ���Ͳ���ͨ����ӳ���ϵ����ֱ���ͷ�ֱ������
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  // �������Ҫ��������źŵķ�Ƶϵ��
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  // �������Ҫ��������źŵ��˲�ϵ��
  TIM_ICInitStructure.TIM_ICFilter = 0;
  // ��ʱ�����벶���ʼ��
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
