/**
  ******************************************************************************
  * @file    spi.h 
  * @author  xiaobo
  * @version V3.5.0
  * @date    20191125
  * @brief   Header for spi.c module.
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPIX_H
#define __SPIX_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SPI_SPIx                      SPI1                        
#define SPI_CLKx                      RCC_APB2Periph_SPI1
#define SPI_SCK_PIN                   GPIO_Pin_5                  /* PA */
#define SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA
#define SPI_MISO_PIN                  GPIO_Pin_6                  /* PA */
#define SPI_MISO_GPIO_PORT            GPIOA                       /* GPIOA */
#define SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA
#define SPI_MOSI_PIN                  GPIO_Pin_7                  /* PA */
#define SPI_MOSI_GPIO_PORT            GPIOA                       /* GPIOA */
#define SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA
#define SPI_NSS_PIN                   GPIO_Pin_4                  /* PA */
#define SPI_NSS_GPIO_PORT             GPIOA                       /* GPIOA */
#define SPI_NSS_GPIO_CLK              RCC_APB2Periph_GPIOA

/* NSS set and reset */
#define SPI_NSS_LOW()       GPIO_ResetBits(SPI_NSS_GPIO_PORT, SPI_NSS_PIN)
#define SPI_NSS_HIGH()      GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_PIN)

/* Exported functions ------------------------------------------------------- */
void SPIx_Init(void);

u8 SPI_ReadByte(u8 TxDate);
void SPI_WriteByte(u8 add, u8 val);

#endif /* __SPIX_H */

/********************************END OF FILE***********************************/


