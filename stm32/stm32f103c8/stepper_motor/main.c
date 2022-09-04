/**
  ******************************************************************************
  * @file    main.c
  * @author  xiaobo
  * @version V3.5.0
  * @date    20191217
  * @brief   Main file.

	*          IN4: PB6  d
  *          IN3: PB5  c
  *          IN2: PB4  b
  *          IN1: PB3  a
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"

/* Private variables ---------------------------------------------------------*/
u8 phasecw[8] ={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};
u8 phaseccw[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};

/* Private functions ---------------------------------------------------------*/
void SetMotor(unsigned char InputData);
void motorNcircle(int n,u8 position, u8 tms); // n:圈数; position:方向; tms:延迟ms;

int main(void)
{
	DelayInit();
	GPIO_Config();

  while(1)
  {				
		motorNcircle(1,1,2);
		DelayS(1);
	}	
}

void SetMotor(unsigned char InputData)
{
	if(InputData&0x01)
		GPIO_SetBits(GPIO_PORT,GPIO_PIN1);
	else
		GPIO_ResetBits(GPIO_PORT,GPIO_PIN1);

	if(InputData&0x02)
		GPIO_SetBits(GPIO_PORT,GPIO_PIN2);
	else
		GPIO_ResetBits(GPIO_PORT,GPIO_PIN2);

	if(InputData&0x04)
		GPIO_SetBits(GPIO_PORT,GPIO_PIN3);
	else
		GPIO_ResetBits(GPIO_PORT,GPIO_PIN3);

	if(InputData&0x08)
		GPIO_SetBits(GPIO_PORT,GPIO_PIN4);
	else
		GPIO_ResetBits(GPIO_PORT,GPIO_PIN4);
}

//步距角5.625 360/5.625=64 减速比1/64
//64*64个脉冲转一圈
//n圈数
//position 方向
void motorNcircle(int n,u8 position, u8 tms)
{
	int i,j,k=0;
	for(j=0;j<n;j++)     // 圈数
	{
		for(i=0;i<50;i++)  // 0.9°=360°/(50齿×8拍)
//		for(i=0;i<512;i++) // 5.625°=360/(8齿×8拍)
		{
			for(k=0;k<8;k++)
			{
				if(1 == position)
					SetMotor(phasecw[k]);
				else
					SetMotor(phaseccw[k]);

				DelayMs(tms);
			}
		}
	}
}

/********************************END OF FILE***********************************/
