/*
 * ��������Key_GPIO_Config
 * ������  ���ð����õ���I/O��
 * ���룺  ��
 * �����  ��
 */
 
#include "key.h" 
 
u8 ReadKeyDown(void);
 
/* ������ʼ�� */
void Key_GPIO_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		/* ���������˿ڵ�ʱ�� */
		RCC_APB2PeriphClockCmd(RCC_KEY1, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_KEY1;        // ѡ��Ҫ���Ƶ�����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   // �������������а���Ӧ�ӵ͵�ƽ
		
		GPIO_Init(GPIO_KEY1_PORT, &GPIO_InitStructure); // ��ʼ������
}
	
/* �ܽ�ɨ�躯�� */
u8 ReadKeyDown(void)
{
	  if(!GPIO_ReadInputDataBit(GPIO_KEY1_PORT, GPIO_KEY1))  // ��鰴���Ƿ��£�Ϊ0����
		{
			return KEY1;
		}
		else
		{
			return NOKEY;
		}
}

