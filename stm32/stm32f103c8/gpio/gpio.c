/*********************** 2018_05_17 *********************
 *文件名  ：gpio.c
 *描述    ：gpio配置函数
 *库版本  ：ST3.5.0
 *********************************************************/
 #include "gpio.h"

/*
 * 函数名：LED_GPIO_Config 
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
 
void GPIO_Config(void)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启GPIOX的外设时钟*/
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);

	/*选择要控制的GPIOX引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN1|GPIO_PIN2|GPIO_PIN3;

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				 //正常点亮

	/*设置引脚模式为输入下拉*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;          //微弱点亮
	/*设置引脚模式为输入上拉*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //微弱点亮
	/*设置引脚模式为输入浮空*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //不点亮
	/*设置引脚模式为模拟输入*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;          //不点亮
	/*设置引脚模式为开漏输出*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;       //正常点亮
	/*设置引脚模式为复用推挽*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //全点亮
	/*设置引脚模式为复用开漏*/
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;        //全点亮
	

	/*设置引脚速率为50MHz*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //引脚的响应速度
	/*设置引脚速率为10MHz*/
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	/*设置引脚速率为2MHz*/	
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	

	/*调用函数，初始化GPIOX*/
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);

	/*关闭所有led灯*/
	GPIO_SetBits(GPIO_PORT, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
	
}

/***************************END OF FILE**********************************/
