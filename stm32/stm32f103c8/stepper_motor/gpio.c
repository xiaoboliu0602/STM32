#include "gpio.h"
 
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORT, &GPIO_InitStructure);

	GPIO_SetBits(GPIO_PORT, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4);
}
