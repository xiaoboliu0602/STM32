#include "iwdg.h"

/*
 * ��������IWDG_Init
 *
 * ������  �������Ź���ʼ������
 *
 * ���룺  pre(Ԥ��Ƶϵ��[4,8,16,32,64,128,256])
 *         rlv(��װ��ֵ[0-0xfff])
 *
 *         IWDG ʹ�� LSI ��Ϊʱ�ӣ�LSI һ���� 30 ~ 60kHz ֮�䣬ͨ��ȡ 40kHz��
 *         ��ʱʱ�䣺
 *             Tout = prv/40 * rlv
 *         ����
 *             IWDG_Config(IWDG_Prescaler_64 ,625);  // IWDG 1s ��ʱ���
 *             (64/40)*625 = 1s
 *
 * �����  ��
 */
void IWDG_Init(uint8_t pre,uint16_t rlv)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // ʹ��
	IWDG_SetPrescaler(pre);                       // ����Ԥ��Ƶֵ
	IWDG_SetReload(rlv);                          // ������װ�Ĵ���ֵ
	IWDG_ReloadCounter();                         // ����װ�Ĵ���ֵ�ŵ���������
	IWDG_Enable();                                // ʹ�� IWDG
}

/*
 * ��������IWDG_FeedDog
 * ������  ι��
 * ���룺  ��
 * �����  ��
 */
void IWDG_FeedDog(void)
{
	IWDG_ReloadCounter();                         // ����װ�Ĵ���ֵ�ŵ���������
}

