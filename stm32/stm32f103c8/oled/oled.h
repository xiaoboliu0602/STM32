/**
  ******************************************************************************
  * @file    oled.h
  * @author  xiaobo
  * @version V3.5.0
  * @date    20191222
  * @brief   Header for oled.c module.
	*          GND   
  *          VCC   5V or 3.3V
  *          SCL   PB6£¨SCL£©
  *          SDA   PB7£¨SDA£© 
  ******************************************************************************
	* OLED video memory format:
  *                          [0]0 1 2 3 ... 127	
  *                          [1]0 1 2 3 ... 127	
  *                          [2]0 1 2 3 ... 127	
  *                          [3]0 1 2 3 ... 127	
  *                          [4]0 1 2 3 ... 127	
  *                          [5]0 1 2 3 ... 127	
  *                          [6]0 1 2 3 ... 127	
  *                          [7]0 1 2 3 ... 127 			
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OLED_H
#define __OLED_H			

/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"	 
#include "stm32f10x.h"   

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

/*------------------------------OLED IIC port --------------------------------*/  					   
#define IIC_SCL_PORT    GPIOB
#define IIC_SDA_PORT    GPIOB

#define IIC_SCL_PIN     GPIO_Pin_6
#define IIC_SDA_PIN     GPIO_Pin_7

#define IIC_SCL_CLK     RCC_APB2Periph_GPIOB
#define IIC_SDA_CLK     RCC_APB2Periph_GPIOB

#define OLED_SCLK_Clr() GPIO_ResetBits(IIC_SCL_PORT,IIC_SCL_PIN)//SCL
#define OLED_SCLK_Set() GPIO_SetBits(IIC_SCL_PORT,IIC_SCL_PIN)

#define OLED_SDIN_Clr() GPIO_ResetBits(IIC_SDA_PORT,IIC_SDA_PIN)//SDA
#define OLED_SDIN_Set() GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN)
 		     
#define OLED_CMD  0	//write command
#define OLED_DATA 1	//write data

/* Exported functions ------------------------------------------------------- */

void OLED_Init(void);

void IIC_Start(void);
void IIC_Stop(void);
void IIC_Wait_Ack(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);

void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    

void OLED_Clear(void);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
void OLED_ShowString(u8 x,unsigned char y, unsigned char *p,unsigned char Char_Size);	 

void OLED_ShowChinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void fill_picture(unsigned char fill_Data);

#endif  /* __OLED_H */

/********************************END OF FILE***********************************/
	 



