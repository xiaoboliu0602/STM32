#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#define RCC_I2Cx     RCC_APB1Periph_I2C1
#define RCC_GPIOx    RCC_APB2Periph_GPIOB

#define GPIOx        GPIOB
#define GPIO_Pin_x1  GPIO_Pin_6
#define GPIO_Pin_x2  GPIO_Pin_7

#define I2Cx         I2C1


/* Private function prototypes -----------------------------------------------*/
void I2C_Configuration(void);
uint8_t I2C_Read(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num);
uint8_t I2C_Write(I2C_TypeDef *I2Cx,uint8_t I2C_Addr,uint8_t addr,uint8_t *buf,uint16_t num);





#endif // __I2C_H

/***************************END OF FILE**********************************/
