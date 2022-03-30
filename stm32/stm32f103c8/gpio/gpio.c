/**
  ******************************************************************************
  * @file    gpio.c
  * @author  Bob
  * @version V3.5.0
  * @date    30-March-2022
  * @brief   GPIO configuration
  ******************************************************************************
  */
 #include "gpio.h"
 
void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_PIN1|GPIO_PIN2|GPIO_PIN3;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(GPIO_PORT, &GPIO_InitStructure);

  GPIO_SetBits(GPIO_PORT, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
}

/*********************************END OF FILE**********************************/
