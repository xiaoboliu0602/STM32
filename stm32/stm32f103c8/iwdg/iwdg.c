#include "iwdg.h"

/*
 * 函数名：IWDG_Init
 *
 * 描述：  独立看门狗初始化函数
 *
 * 输入：  pre(预分频系数[4,8,16,32,64,128,256])
 *         rlv(重装载值[0-0xfff])
 *
 *         IWDG 使用 LSI 作为时钟，LSI 一般在 30 ~ 60kHz 之间，通常取 40kHz。
 *         超时时间：
 *             Tout = prv/40 * rlv
 *         例：
 *             IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s 超时溢出
 *             (64/40)*625 = 1s
 *
 * 输出：  无
 */
void IWDG_Init(uint8_t pre,uint16_t rlv)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // 使能
	IWDG_SetPrescaler(pre);                       // 设置预分频值
	IWDG_SetReload(rlv);                          // 设置重装寄存器值
	IWDG_ReloadCounter();                         // 把重装寄存器值放到计数器中
	IWDG_Enable();                                // 使能 IWDG
}

/*
 * 函数名：IWDG_FeedDog
 * 描述：  喂狗
 * 输入：  无
 * 输出：  无
 */
void IWDG_FeedDog(void)
{
	IWDG_ReloadCounter();                         // 把重装寄存器值放到计数器中
}

