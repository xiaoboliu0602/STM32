/*
 * 函数名：Key_GPIO_Config
 * 描述：  配置按键用到的I/O口
 * 输入：  无
 * 输出：  无
 */
 
#include "key.h" 
 
u8 ReadKeyDown(void);
 
/* 按键初始化 */
void Key_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		/* 开启按键端口的时钟 */
		RCC_APB2PeriphClockCmd(RCC_KEY1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_KEY1;        // 选择要控制的引脚
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   // 输入上拉，所有按下应接低电平
		
		GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure); // 初始化引脚
}
	
/* 管脚扫描函数 */
u8 ReadKeyDown(void)
{
	  if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT, GPIO_KEY1))  // 检查按键是否按下，为0则按下
		{
			return KEY1;
		}
		else
		{
			return NOKEY;
		}
}

