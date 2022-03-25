/*********************** 2021_04_04 *********************
 *文件名  ：ym1602c.c
 *描述    ：gpio 应用函数库
 *硬件连接：----------------
          
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/
#include "ym1602c.h"
 
// 显示屏命令写入函数
void LCD_write_com(unsigned char com)
{
	RS_CLR;
	RW_CLR;
	EN_SET;
	DATA_OUT = com;
	delay_us(40);   // 官方给出的时间是最低40us
	EN_CLR;
}

void LCD_write_Data(unsigned char data)
{
	RS_SET;
	RW_CLR;
	EN_SET;
	DATA_OUT = data;
	delay_us(40);   // 官方给出的时间是最低40us
	EN_CLR;
}

void LCD_clear(void)
{
	LCD_write_com(0x01);
	delay_ms(5);
}
// 写入字符串
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s)
{
	if (y == 0) 
		LCD_write_com(0x80 + x);
  else 
		LCD_write_com(0xC0 + x);
  while (*s) 
  {
    LCD_write_Data( *s);
    s++;
  }
}
// 写入单个字符(输入字符的 ASCII)
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data) 
{     
  if (y == 0)
		LCD_write_com(0x80 + x);
  else
		LCD_write_com(0xC0 + x);	

  LCD_write_Data( Data);  
}

void LCD_init(void) 
{
  LCD_write_com(0x38);    /*显示模式设置*/ 
  delay_ms(5); 
//  LCD_write_com(0x38); 
//  delay_ms(5);
//  LCD_write_com(0x38); 
//  Ddelay_ms(5);
//  LCD_write_com(0x38);  
//  LCD_write_com(0x08);    /*显示关闭*/ 
//	delay_ms(5);
//  LCD_write_com(0x01);    /*显示清屏*/ 
//	delay_ms(5);
  LCD_write_com(0x06);    /*显示光标移动设置*/ 
  delay_ms(5);
  LCD_write_com(0x0C);    /*显示开及光标设置*/
	delay_ms(5);
}



