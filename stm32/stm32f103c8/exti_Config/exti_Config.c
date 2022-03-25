/*********************** 2018_05_18 *********************
 *文件名  ：exti_Config.c
 *描述    ：中断配置函数
 *硬件连接：PX设为外部中断
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/

 #include "exti_Config.h"

 static void NVIC_Configuration(void); //配置嵌套向量中断控制器
 
/*
 * 函数名：EXTI_PX_Config
 * 描述  ：配置PX为线中断口，设置中断优先级
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
 
 void EXTI_PX_Config(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	 
	 /* config the extiline clock and AFIO clock */
	 RCC_APB2PeriphClockCmd(PX2_INT_GPIO_CLK, ENABLE);  
	 
	 /* config the NVIC */
	 NVIC_Configuration();
/*--------------------------- PX配置 ----------------------------------*/ 
	 /* EXTI line gpio config */
	 //GPIO_InitStructure.GPIO_Pin = PX_INT_GPIO_PIN;
   //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //浮空输入
	 //GPIO_Init(PX_INT_GPIO_PORT, &GPIO_InitStructure);       //调用函数初始化
	 
	 /* EXTI line mode config */
	 //GPIO_EXTILineConfig(PX_INT_EXTI_PORTSOURCE, PX_INT_EXTI_PINSOURCE);      //选择管脚为外部中断线
	 //EXTI_InitStructure.EXTI_Line = PX_INT_EXTI_LINE;                         //选择外部中断线
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                      //设置EXTI线路为中断请求
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;                        //设置EXTI线路为事件请求
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                //设置输入线路下降沿为中断请求
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 //设置输入线路上升沿为中断请求
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;         //设置输入线路上升和下降沿为中断请求
	 
	 //EXTI_InitStructure.EXTI_LineCmd = ENABLE;   //使能外部中断
	 //EXTI_Init(&EXTI_InitStructure);
/*---------------------------PX配置 end----------------------------------*/  
	 
/*--------------------------- PX2配置 ----------------------------------*/ 
	 /* EXTI line gpio config */
	 GPIO_InitStructure.GPIO_Pin = PX2_INT_GPIO_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	          //上拉输入
	 GPIO_Init(PX2_INT_GPIO_PORT, &GPIO_InitStructure);       //调用函数初始化
	 
	 /* EXTI line mode config */
	 GPIO_EXTILineConfig(PX2_INT_EXTI_PORTSOURCE, PX2_INT_EXTI_PINSOURCE);      //选择管脚为外部中断线
	 EXTI_InitStructure.EXTI_Line = PX2_INT_EXTI_LINE;                         //选择外部中断线
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                      //设置EXTI线路为中断请求
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;                        //设置EXTI线路为事件请求
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                //设置输入线路下降沿为中断请求
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 //设置输入线路上升沿为中断请求
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;         //设置输入线路上升和下降沿为中断请求
	 
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;   //使能外部中断
	 EXTI_Init(&EXTI_InitStructure);
/*---------------------------PX2配置 end----------------------------------*/  
		 
	 
 }
 
/*
 * 函数名：NVIC_Configuration
 * 描述  ：配置嵌套向量中断控制器NVIC
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
 
 static void NVIC_Configuration(void)
 {
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 /* 设置优先级分组，只能设置一次 */
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  //设置优先级分组：先占优先级0位，从优先级4位
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //设置优先级分组：先占优先级1位，从优先级3位
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置优先级分组：先占优先级2位，从优先级2位
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  //设置优先级分组：先占优先级3位，从优先级1位
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //设置优先级分组：先占优先级4位，从优先级0位
	 
	 /* Configure */
	 //NVIC_InitStructure.NVIC_IRQChannel = PX_INT_EXTI_IRQ;     //使能外部中断线
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          //使能外部中断线0
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;          //使能外部中断线1
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;					 //使能外部中断线2
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;          //使能外部中断线3
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;          //使能外部中断线4
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;      //使能外部中断线15-10
	 
	 //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //设置先占优先级0~15 与从占优先级共占4位
	 	 
	 //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //设置从占优先级0~15 与先占优先级共占4位
	 
	 //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 //NVIC_Init(&NVIC_InitStructure);
	 
	 /* 配置PX2*/
	 NVIC_InitStructure.NVIC_IRQChannel = PX2_INT_EXTI_IRQ;
	 
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //设置先占优先级0~15 与从占优先级共占4位
	 	 
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	 
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);
 
 }
 
