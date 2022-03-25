/*********************** 2021_04_19*********************
 *�ļ���  ��timer.c
 *����    ����ʱ��
 *Ӳ�����ӣ�
 *��汾  ��ST3.5.0
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
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ),�ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
  TIM_TimeBaseStructure.TIM_Period = (10000 - 1);
	
	/* ʱ��Ԥ��Ƶ��   ���磺ʱ��Ƶ��=72MHZ/(ʱ��Ԥ��Ƶ+1) */
//  TIM_TimeBaseStructure.TIM_Prescaler= (36000 - 1);	
	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
	
	/*
		ʹ�ü�ʱ���жϸı� IO �ڵ�ƽ���ж�һ�α仯һ�ε�ƽ��
	
		�� TIM_Prescaler = (72 - 1) ʱ��
	
				TIM_Period					ʾ����ʵ��Ƶ��   ��ʱֵ
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
				 
		���ԣ�TIM_Period �ļ���ֵӦΪ (n - 1), nΪĿ���ʱ΢��ֵ��
		ע�⣺TIM_Period ����Ϊ 0 ������
	*/
  
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 			/* ������Ƶ */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/* ���ϼ���ģʽ */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             /* ��ʼ�� TIMx ʱ����� */
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);				/* �������жϱ�־ */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    /* ������ʱ�������ж� */
  TIM_Cmd(TIM2, ENABLE);											/* ����ʱ�� */
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
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // �����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	      // ��
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
	
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) // �ж��жϱ�־λ
	{
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);      // ����жϱ�־λ
      
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
