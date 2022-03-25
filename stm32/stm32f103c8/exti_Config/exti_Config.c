/*********************** 2018_05_18 *********************
 *�ļ���  ��exti_Config.c
 *����    ���ж����ú���
 *Ӳ�����ӣ�PX��Ϊ�ⲿ�ж�
 *��汾  ��ST3.5.0
 *********************************************************/

 #include "exti_Config.h"

 static void NVIC_Configuration(void); //����Ƕ�������жϿ�����
 
/*
 * ��������EXTI_PX_Config
 * ����  ������PXΪ���жϿڣ������ж����ȼ�
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
 
 void EXTI_PX_Config(void)
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
	 
	 /* config the extiline clock and AFIO clock */
	 RCC_APB2PeriphClockCmd(PX2_INT_GPIO_CLK, ENABLE);  
	 
	 /* config the NVIC */
	 NVIC_Configuration();
/*--------------------------- PX���� ----------------------------------*/ 
	 /* EXTI line gpio config */
	 //GPIO_InitStructure.GPIO_Pin = PX_INT_GPIO_PIN;
   //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	 //��������
	 //GPIO_Init(PX_INT_GPIO_PORT, &GPIO_InitStructure);       //���ú�����ʼ��
	 
	 /* EXTI line mode config */
	 //GPIO_EXTILineConfig(PX_INT_EXTI_PORTSOURCE, PX_INT_EXTI_PINSOURCE);      //ѡ��ܽ�Ϊ�ⲿ�ж���
	 //EXTI_InitStructure.EXTI_Line = PX_INT_EXTI_LINE;                         //ѡ���ⲿ�ж���
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                      //����EXTI��·Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;                        //����EXTI��·Ϊ�¼�����
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                //����������·�½���Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 //����������·������Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;         //����������·�������½���Ϊ�ж�����
	 
	 //EXTI_InitStructure.EXTI_LineCmd = ENABLE;   //ʹ���ⲿ�ж�
	 //EXTI_Init(&EXTI_InitStructure);
/*---------------------------PX���� end----------------------------------*/  
	 
/*--------------------------- PX2���� ----------------------------------*/ 
	 /* EXTI line gpio config */
	 GPIO_InitStructure.GPIO_Pin = PX2_INT_GPIO_PIN;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	          //��������
	 GPIO_Init(PX2_INT_GPIO_PORT, &GPIO_InitStructure);       //���ú�����ʼ��
	 
	 /* EXTI line mode config */
	 GPIO_EXTILineConfig(PX2_INT_EXTI_PORTSOURCE, PX2_INT_EXTI_PINSOURCE);      //ѡ��ܽ�Ϊ�ⲿ�ж���
	 EXTI_InitStructure.EXTI_Line = PX2_INT_EXTI_LINE;                         //ѡ���ⲿ�ж���
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;                      //����EXTI��·Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;                        //����EXTI��·Ϊ�¼�����
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;                //����������·�½���Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;                 //����������·������Ϊ�ж�����
	 //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;         //����������·�������½���Ϊ�ж�����
	 
	 EXTI_InitStructure.EXTI_LineCmd = ENABLE;   //ʹ���ⲿ�ж�
	 EXTI_Init(&EXTI_InitStructure);
/*---------------------------PX2���� end----------------------------------*/  
		 
	 
 }
 
/*
 * ��������NVIC_Configuration
 * ����  ������Ƕ�������жϿ�����NVIC
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
 
 static void NVIC_Configuration(void)
 {
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 /* �������ȼ����飬ֻ������һ�� */
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  //�������ȼ����飺��ռ���ȼ�0λ�������ȼ�4λ
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);    //�������ȼ����飺��ռ���ȼ�1λ�������ȼ�3λ
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�������ȼ����飺��ռ���ȼ�2λ�������ȼ�2λ
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  //�������ȼ����飺��ռ���ȼ�3λ�������ȼ�1λ
	 //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  //�������ȼ����飺��ռ���ȼ�4λ�������ȼ�0λ
	 
	 /* Configure */
	 //NVIC_InitStructure.NVIC_IRQChannel = PX_INT_EXTI_IRQ;     //ʹ���ⲿ�ж���
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          //ʹ���ⲿ�ж���0
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;          //ʹ���ⲿ�ж���1
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;					 //ʹ���ⲿ�ж���2
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;          //ʹ���ⲿ�ж���3
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;          //ʹ���ⲿ�ж���4
	 //NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;      //ʹ���ⲿ�ж���15-10
	 
	 //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //������ռ���ȼ�0~15 ���ռ���ȼ���ռ4λ
	 	 
	 //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //���ô�ռ���ȼ�0~15 ����ռ���ȼ���ռ4λ
	 
	 //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 //NVIC_Init(&NVIC_InitStructure);
	 
	 /* ����PX2*/
	 NVIC_InitStructure.NVIC_IRQChannel = PX2_INT_EXTI_IRQ;
	 
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //������ռ���ȼ�0~15 ���ռ���ȼ���ռ4λ
	 	 
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	 
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);
 
 }
 
