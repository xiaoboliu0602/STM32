/*********************** 2016_03_11 *********************
 *�ļ���  ��delay.c
 *����    ������delay����?
 *Ӳ�����ӣ�----------------
 *��汾  ��ST3.5.0
 *********************************************************/
#include "delay.h"

static u8  fac_us = 0; //us��ʱ����
static u16 fac_ms = 0; //ms��ʱ����

/**
 * @brief  delay time config
 * @param  None
 * @retval None
 */
 
void DelayInit()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //ѡ���ⲿʱ�� HCLK/8
	fac_us = SystemCoreClock/8000000;                        //ϵͳʱ�ӵ�1/8
	fac_ms = (u16)fac_us*1000;         //��ucos�£�����ÿ��ms��Ҫ��systickʱ����
}

 
/**
 * @brief  delay time us
 * @param  None
 * @retval None
 */

void delay_us(u32 nus)
{
	u32 temp;
	SysTick -> LOAD = nus * fac_us;             //ʱ�����
	SysTick -> VAL = 0x00;                      //��ռ�����
	SysTick -> CTRL|= SysTick_CTRL_ENABLE_Msk;  //��ʼ����
	do
	{
		temp = SysTick -> CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
	SysTick -> CTRL&=~SysTick_CTRL_ENABLE_Msk;  //�رռ�����
	SysTick -> VAL = 0x00;                     //��ռ�����	 
}

 
/**
  * @brief  delay time ms
  * @param  None
  * @retval SysTick -> LOADΪ24λ�Ĵ��������������ʱΪ
  *         nms <= 0xffffff*8*1000/SYSCLK  (Hz)
  *         ��72MHz�����£�nms <= 1864
  */

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick -> LOAD = (u32)nms * fac_ms;
	SysTick -> VAL = 0x00;
	SysTick -> CTRL|= SysTick_CTRL_ENABLE_Msk; 
	do
	{
		temp = SysTick -> CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
	SysTick -> CTRL&=~SysTick_CTRL_ENABLE_Msk;  //�رռ�����
	SysTick -> VAL = 0x00;                     //��ռ�����	 
}

 
/**
  * @brief  delay time s
  * @param  None
  * @retval None
  */

void delay_s(u16 ns)
{
	unsigned char i;
	for(i=0; i<ns; i++)
	{
		delay_ms(1000);
	}
}

/*��ʱ*/
void delay2(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}
