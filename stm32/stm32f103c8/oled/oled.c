/**
  ******************************************************************************
  * @file    oled.c
  * @version V3.5.0
  * @date    20191222
  * @brief   0.69 inch OLED configuration file. IIC format
	*          GND   
  *          VCC   5V or 3.3V
  *          SCL   PB6��SCL��
  *          SDA   PB7��SDA�� 
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
	
/* Includes ------------------------------------------------------------------*/
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/	
/* Private function prototypes -----------------------------------------------*/	
	
/* Private functions ---------------------------------------------------------*/	

/**
  * @brief  IIC Start  1
  * @param  None
  * @retval None
  */	
void IIC_Start()
{
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**
  * @brief  IIC Stop  2
  * @param  None
  * @retval None
  */
void IIC_Stop()
{
  OLED_SCLK_Set();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

/**
  * @brief  IIC Wait Ack  3
  * @param  None
  * @retval None
  */
void IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}

/**
  * @brief  IIC Write byte  4
  * @param  IIC_Byte
  * @retval None
  */
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i,m,da;
	
	da = IIC_Byte;
	OLED_SCLK_Clr();
	
	for(i=0;i<8;i++)		
	{
		m = da;
		//OLED_SCLK_Clr();
		m = m & 0x80;
		if(m==0x80)
		{
		  OLED_SDIN_Set();
		}
		else 
		{
			OLED_SDIN_Clr();
		}
		da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}

/**
  * @brief  IIC Write Command  5
  * @param  IIC_Command
  * @retval None
  */
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
  Write_IIC_Byte(0x78);       //Slave address,SA0=0
	IIC_Wait_Ack();	
  Write_IIC_Byte(0x00);			  //write command
	IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
  IIC_Stop();
}

/**
  * @brief  IIC Write Data  6
  * @param  IIC_Data
  * @retval None
  */
void Write_IIC_Data(unsigned char IIC_Data)
{
  IIC_Start();
  Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
  Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
  IIC_Stop();
}

/**
  * @brief  IIC Write Byte  7
  * @param  dat,cmd
  * @retval None
  */
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
    Write_IIC_Data(dat);  
	}
  else 
	{
    Write_IIC_Command(dat);
	}
}

/**
  * @brief  Display Picture  8
  * @param  fill_Data
  * @retval None
  */
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);	  	//low column start address
		OLED_WR_Byte(0x10,0);		  //high column start address
		for(n=0;n<128;n++)
		{
		  OLED_WR_Byte(fill_Data,1);
		}
	}
}

/**
  * @brief  Set coordinate  9
  * @param  (x,y)
  * @retval None
  */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}

/**
  * @brief  OLED Display ON  10
  * @param  None
  * @retval None
  */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/**
  * @brief  OLED Display OFF  11
  * @param  None
  * @retval None
  */     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		 

/**
  * @brief  Clear OLED  12
  * @param  None
  * @retval None
  */
void OLED_Clear(void)  
{  
	unsigned char i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
		{
		  OLED_WR_Byte(0,OLED_DATA);
    }			
	} 
}

/**
  * @brief  Display one character at the specified position.  13
  * @param  (x,y),chr,Char_Size
  * @retval None
  */
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{      	
	unsigned char c=0,i=0;	
	c = chr-' ';         //�õ�ƫ�ƺ��ֵ			
	if(x > Max_Column-1)
  {
	  x = 0;
		y = y + 2;
	}
	if(Char_Size == 16)
	{
	  OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
	{	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WR_Byte(F6x8[c][i],OLED_DATA);
	}
}

/**
  * @brief  m^n  
  * @param  m,n
  * @retval result = m^n
  */
u32 oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result = 1;	 
	while(n--)
	{
	  result *= m;
	}    
	return result;
}

/**
  * @brief  Display one number at the specified position.  14
  * @param  (x,y),num,len,size2
  * @retval None
  */ 
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{         	
	unsigned char t,temp;
	unsigned char enshow = 0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow == 0&&t<(len-1))
		{
			if(temp == 0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}
			else enshow = 1; 		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

/**
  * @brief  Display one string at the specified position.  15
  * @param  (x,y),*chr,Char_Size
  * @retval None
  */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size)
{
	unsigned char j = 0;
	while(chr[j] != '\0')
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);
		x += 8;
		if(x>120)
    {
		  x = 0;
		  y += 2;
		}
		j++;
	}
}

/**
  * @brief  Display one Chinese character at the specified position.  16
  * @param  (x,y),no
  * @retval None
  */
void OLED_ShowChinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0;
	OLED_Set_Pos(x,y);	
  for(t=0;t<20;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
	  adder+=1;
  }	
	OLED_Set_Pos(x,y+1);	
  for(t=0;t<20;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
  }					
}

/**
  * @brief  Display one BMP picture at the specified position.  17
  * @param  (x0,y0),(x1,y1),BMP[]
  * @retval None
  */
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) 
		y=y1/8;      
  else 
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	  {      
	  	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	  }
	}
} 

/**
  * @brief  Initialize SSD1306  18
  * @param  None
  * @retval None
  */
void OLED_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(IIC_SCL_CLK, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(IIC_SCL_PORT,IIC_SCL_PIN);	
	
	RCC_APB2PeriphClockCmd(IIC_SDA_CLK, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
 	GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN);		

  OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD);//--contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	
	OLED_WR_Byte(0xA1,OLED_CMD);//--set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//--Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//--set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//--set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//--set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//--Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//--set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//--set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  



