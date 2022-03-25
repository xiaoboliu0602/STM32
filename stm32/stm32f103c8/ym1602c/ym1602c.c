/*********************** 2021_04_04 *********************
 *�ļ���  ��ym1602c.c
 *����    ��gpio Ӧ�ú�����
 *Ӳ�����ӣ�----------------
 *��汾  ��ST3.5.0
 *********************************************************/
#include "ym1602c.h"
 
// ��ʾ������д�뺯��
void LCD_write_com(unsigned char com)
{
	RS_CLR;
	RW_CLR;
	EN_SET;
	DATA_OUT = com;
	delay_us(40);   // �ٷ�������ʱ�������40us
	EN_CLR;
}

void LCD_write_Data(unsigned char data)
{
	RS_SET;
	RW_CLR;
	EN_SET;
	DATA_OUT = data;
	delay_us(40);   // �ٷ�������ʱ�������40us
	EN_CLR;
}

void LCD_clear(void)
{
	LCD_write_com(0x01);
	delay_ms(5);
}
// д���ַ���
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
// д�뵥���ַ�(�����ַ��� ASCII)
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
  LCD_write_com(0x38);    /*��ʾģʽ����*/ 
  delay_ms(5); 
//  LCD_write_com(0x38); 
//  delay_ms(5);
//  LCD_write_com(0x38); 
//  Ddelay_ms(5);
//  LCD_write_com(0x38);  
//  LCD_write_com(0x08);    /*��ʾ�ر�*/ 
//	delay_ms(5);
//  LCD_write_com(0x01);    /*��ʾ����*/ 
//	delay_ms(5);
  LCD_write_com(0x06);    /*��ʾ����ƶ�����*/ 
  delay_ms(5);
  LCD_write_com(0x0C);    /*��ʾ�����������*/
	delay_ms(5);
}



