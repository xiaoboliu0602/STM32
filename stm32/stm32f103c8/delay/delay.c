/*********************** 2016_03_11 *********************
 *文件名  ：delay.c
 *描述    ：常用delay函数?
 *硬件连接：----------------
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/
#include "delay.h"

static u8  fac_us = 0; //us延时倍乘
static u16 fac_ms = 0; //ms延时倍乘

/**
 * @brief  delay time config
 * @param  None
 * @retval None
 */
 
void DelayInit()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //选择外部时钟 HCLK/8
	fac_us = SystemCoreClock/8000000;                        //系统时钟的1/8
	fac_ms = (u16)fac_us*1000;         //非ucos下，代表每个ms需要的systick时钟数
}

 
/**
 * @brief  delay time us
 * @param  None
 * @retval None
 */

void delay_us(u32 nus)
{
	u32 temp;
	SysTick -> LOAD = nus * fac_us;             //时间加载
	SysTick -> VAL = 0x00;                      //清空计数器
	SysTick -> CTRL|= SysTick_CTRL_ENABLE_Msk;  //开始倒数
	do
	{
		temp = SysTick -> CTRL;
	}
	while(temp & 0x01 && !(temp & (1 << 16))); //等待时间到达
	SysTick -> CTRL&=~SysTick_CTRL_ENABLE_Msk;  //关闭计数器
	SysTick -> VAL = 0x00;                     //清空计数器	 
}

 
/**
  * @brief  delay time ms
  * @param  None
  * @retval SysTick -> LOAD为24位寄存器，所以最大延时为
  *         nms <= 0xffffff*8*1000/SYSCLK  (Hz)
  *         在72MHz条件下，nms <= 1864
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
	while(temp & 0x01 && !(temp & (1 << 16))); //等待时间到达
	SysTick -> CTRL&=~SysTick_CTRL_ENABLE_Msk;  //关闭计数器
	SysTick -> VAL = 0x00;                     //清空计数器	 
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

/*延时*/
void delay2(__IO u32 nCount)
{
	for(; nCount != 0; nCount--);
}
