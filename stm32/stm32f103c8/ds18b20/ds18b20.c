/*********************** 2018_06_07 *********************
 *文件名  ：ds18b20.c
 *描述    ：ds18b20驱动函数
 *硬件连接：----------------
 *库版本  ：ST3.5.0
 *作者    ：xiaoboliu
 *********************************************************/
#include "ds18b20.h"

/*设置管脚为输入*/
void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_DQ_IN_CLK, ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin = DS18B20_DQ_IN_PIN;	   //温度传感器DQ管脚
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		   //输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_DQ_IN_PORT, &GPIO_InitStructure);
}
/*设置管脚位输出*/
void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_DQ_OUT_CLK, ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin = DS18B20_DQ_OUT_PIN;	   //温度传感器DQ管脚
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*初始化*/
u8 DS18B20_Init(void)
{ 	
	u8 i;
	
	DS18B20_IO_OUT();    //设置管脚为输出	
	Set_DS18B20_DQ_OUT;  //DQ=1
	delay_us(1);
	Clr_DS18B20_DQ_OUT;  //DQ=0
	delay_us(500);       //拉低总线500us
	Set_DS18B20_DQ_OUT;  //DQ=1 释放总线
	
	DS18B20_IO_IN();     //设置管脚为输入	
	delay_us(38);        //延时38us 等待读取
	//读取
  i=GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT,DS18B20_DQ_IN_PIN);
	
	delay_us(140);
	Set_DS18B20_DQ_OUT;  //DQ=1
  delay_us(1);
	
	return i;
}

/*写控制器0/1*/
void write_byte(unsigned char dat)  //传输一个字节
{
//产生一个字节，至少要将总线拉低1us，数据从低位向高位发送；
	unsigned char i;
	DS18B20_IO_OUT();    //设置管脚为输出	
	for(i=0;i<8;i++)
	{
		Clr_DS18B20_DQ_OUT;  //DQ=0
		delay_us(1);         //产生写时序
		if(dat&0x01)
		{
			Set_DS18B20_DQ_OUT;  //DQ=1
		}
		else
		{
			Clr_DS18B20_DQ_OUT;  //DQ=0
		}
		delay_us(77);          //延时77us
		Set_DS18B20_DQ_OUT;    //DQ=1 释放总线准备下一次数据写入
		delay_us(1);
		dat>>=1;
	}
}

/*读取数据*/
unsigned char read_byte()
{
	unsigned char dat, i ,j;
	for(i=0;i<8;i++)
	{
		DS18B20_IO_OUT();    //设置管脚为输出
		Clr_DS18B20_DQ_OUT;  //DQ=0
		delay_us(1);         //产生读时序
		Set_DS18B20_DQ_OUT;  //DQ=1
		delay_us(1);         //释放总线
		
		DS18B20_IO_IN();     //设置管脚为输入	
		j=GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT,DS18B20_DQ_IN_PIN);
		delay_us(77);        //延时77us
		DS18B20_IO_OUT();    //设置管脚为输出
		Set_DS18B20_DQ_OUT;  //DQ=1
		delay_us(1);
		dat=(j<<7)|(dat>>1); //数据从低位传向高位
	}
	return dat;
}

/*一次温度读取*/  // 仅读取正温度
double DS18B20_data(void)
{
	int d=0;
	unsigned char L,M;

	DS18B20_Init();
	write_byte(0xcc); //发送忽略ROM指令
  write_byte(0x44); //发送温度转换指令
	DS18B20_Init();
  write_byte(0xcc); //发送忽略ROM指令
  write_byte(0xbe); //读取DS18B20暂存器值
	L = read_byte();  //先接收低八位
	M = read_byte();  //再接收高八位
	d = M;
	d<<=8;
	d|=L;
	
	return d*0.0625;
}







