/*********************** 2018_05_17 *********************
 *文件名  ：gpio.c
 *描述    ：gpio 配置函数
 *硬件连接：

 *库版本  ：ST3.5.0
 *作者    ：xiaobo
 *********************************************************/
#include "gpio.h"

/*
 * 函数名：GPIO_Config
 * 描述  ：I/O口
 * 输入  ：无
 * 输出  ：无
 */
 
void GPIO_Config(void)
{
    /* 定义一个 GPIO_InitTypeDef 类型的结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启 GPIOX 外设时钟 */
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);

	/* 选择要控制的 GPIOX 引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN1|GPIO_PIN2|GPIO_PIN3;

	/* 设置引脚模式为通用推挽输出 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				 // 正常点亮

	/* 输入下拉 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;          // 微弱点亮
	/* 输入上拉 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          // 微弱点亮
	/* 输入浮空 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // 不点亮
	/* 模拟输入 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          // 不点亮
	/* 开漏输出 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;       // 正常点亮
	/* 复用推挽 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        // 全点亮
	/* 复用开漏 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;        // 全点亮
	

	/* 设置引脚速率为 50MHz */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 引脚响应速度
	/* 设置引脚速率为 10MHz */
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	/* 设置引脚速率为 2MHz */
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;


	/* 调用函数，初始化 GPIOX */
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);

	/* 置位 */
	GPIO_SetBits(GPIO_PORT, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);

}

/***************************END OF FILE**********************************/
