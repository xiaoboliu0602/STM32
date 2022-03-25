#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "max30102.h"


/* Private define ------------------------------------------------------------*/
#define SCL_H         GPIOB->BSRR = GPIO_Pin_6	 /* GPIO_SetBits(GPIOB , GPIO_Pin_6)   */
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6   /* GPIO_ResetBits(GPIOB , GPIO_Pin_6) */
   
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7	 /* GPIO_SetBits(GPIOB , GPIO_Pin_7)   */
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7	 /* GPIO_ResetBits(GPIOB , GPIO_Pin_7) */

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6   /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_6) */
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7	 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_7) */

/* Private function prototypes -----------------------------------------------*/

void    I2C_Configuration(void);
void    I2C_delay(void);
void    I2C_SendByte(uint8_t SendByte);
uint8_t I2C_ReceiveByte(void);

FunctionalState I2C_WriteByte(uint8_t SendByte, uint8_t WriteAddress);
FunctionalState I2C_ReadByte(uint8_t* pBuffer, uint16_t length, uint8_t ReadAddress);

#endif // __I2C_H

