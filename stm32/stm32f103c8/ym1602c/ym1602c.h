#ifndef __YM1602C_H
#define __YM1602C_H

#include "stm32f10x.h"

#include "gpio.h"
#include "delay.h"

// ÏÔÊ¾ÆÁÃüÁîĞ´Èëº¯Êı
void LCD_write_com(unsigned char com);
void LCD_write_Data(unsigned char data);
void LCD_clear(void);
void LCD_write_str(unsigned char x,unsigned char y,unsigned char *s);
void LCD_write_char(unsigned char x,unsigned char y,unsigned char Data);

void LCD_init(void);

#endif // __YM1602C_H
