/*********************** 2018_06_07 *********************
 *�ļ���  ��ds18b20.c
 *����    ��ds18b20��������
 *Ӳ�����ӣ�----------------
 *��汾  ��ST3.5.0
 *********************************************************/
#include "ds18b20.h"

/*���ùܽ�Ϊ����*/
void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_DQ_IN_CLK, ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin = DS18B20_DQ_IN_PIN;	   //�¶ȴ�����DQ�ܽ�
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		   //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_DQ_IN_PORT, &GPIO_InitStructure);
}
/*���ùܽ�λ���*/
void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(DS18B20_DQ_OUT_CLK, ENABLE);	 
	
	GPIO_InitStructure.GPIO_Pin = DS18B20_DQ_OUT_PIN;	   //�¶ȴ�����DQ�ܽ�
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DS18B20_DQ_OUT_PORT, &GPIO_InitStructure);
}

/*��ʼ��*/
u8 DS18B20_Init(void)
{ 	
	u8 i;
	
	DS18B20_IO_OUT();    //���ùܽ�Ϊ���	
	Set_DS18B20_DQ_OUT;  //DQ=1
	delay_us(1);
	Clr_DS18B20_DQ_OUT;  //DQ=0
	delay_us(500);       //��������500us
	Set_DS18B20_DQ_OUT;  //DQ=1 �ͷ�����
	
	DS18B20_IO_IN();     //���ùܽ�Ϊ����	
	delay_us(38);        //��ʱ38us �ȴ���ȡ
	//��ȡ
  i=GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT,DS18B20_DQ_IN_PIN);
	
	delay_us(140);
	Set_DS18B20_DQ_OUT;  //DQ=1
  delay_us(1);
	
	return i;
}

/*д������0/1*/
void write_byte(unsigned char dat)  //����һ���ֽ�
{
//����һ���ֽڣ�����Ҫ����������1us�����ݴӵ�λ���λ���ͣ�
	unsigned char i;
	DS18B20_IO_OUT();    //���ùܽ�Ϊ���	
	for(i=0;i<8;i++)
	{
		Clr_DS18B20_DQ_OUT;  //DQ=0
		delay_us(1);         //����дʱ��
		if(dat&0x01)
		{
			Set_DS18B20_DQ_OUT;  //DQ=1
		}
		else
		{
			Clr_DS18B20_DQ_OUT;  //DQ=0
		}
		delay_us(77);          //��ʱ77us
		Set_DS18B20_DQ_OUT;    //DQ=1 �ͷ�����׼����һ������д��
		delay_us(1);
		dat>>=1;
	}
}

/*��ȡ����*/
unsigned char read_byte()
{
	unsigned char dat, i ,j;
	for(i=0;i<8;i++)
	{
		DS18B20_IO_OUT();    //���ùܽ�Ϊ���
		Clr_DS18B20_DQ_OUT;  //DQ=0
		delay_us(1);         //������ʱ��
		Set_DS18B20_DQ_OUT;  //DQ=1
		delay_us(1);         //�ͷ�����
		
		DS18B20_IO_IN();     //���ùܽ�Ϊ����	
		j=GPIO_ReadInputDataBit(DS18B20_DQ_IN_PORT,DS18B20_DQ_IN_PIN);
		delay_us(77);        //��ʱ77us
		DS18B20_IO_OUT();    //���ùܽ�Ϊ���
		Set_DS18B20_DQ_OUT;  //DQ=1
		delay_us(1);
		dat=(j<<7)|(dat>>1); //���ݴӵ�λ�����λ
	}
	return dat;
}

/*һ���¶ȶ�ȡ*/  // ����ȡ���¶�
double DS18B20_data(void)
{
	int d=0;
	unsigned char L,M;

	DS18B20_Init();
	write_byte(0xcc); //���ͺ���ROMָ��
  write_byte(0x44); //�����¶�ת��ָ��
	DS18B20_Init();
  write_byte(0xcc); //���ͺ���ROMָ��
  write_byte(0xbe); //��ȡDS18B20�ݴ���ֵ
	L = read_byte();  //�Ƚ��յͰ�λ
	M = read_byte();  //�ٽ��ո߰�λ
	d = M;
	d<<=8;
	d|=L;
	
	return d*0.0625;
}







