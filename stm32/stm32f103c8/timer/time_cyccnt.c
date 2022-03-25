/*
************************************************************************************************************************
*                                             ʱ�����ؼĴ�������
************************************************************************************************************************
*/
/*
 ��Cortex-M3������һ������DWT(Data Watchpoint and Trace),��������һ��32λ�Ĵ���CYCCNT,����һ�����ϼ�������
 ��¼�����ں�ʱ�����еĸ�������ܼ�¼��ʱ��Ϊ��60s=2��32�η�/72000000(�����ں�Ƶ��Ϊ72M,�ں���һ�ε�ʱ����Ϊ1/72M=14ns)
 ��CYCCNT���֮��,����0���¿�ʼ���ϼ�����
 
 ʹ��CYCCNT�����Ĳ�������:
 1��ʹ��DWT����,������ں˵��ԼĴ���DEMCR��λ24���ƣ�д1ʹ��
 2��ʹ��CYCCNT�Ĵ���֮ǰ������0
 3��ʹ��CYCCNT�Ĵ����������DWT_CTRL(�����Ϻ궨��ΪDWT_CR)��λ0����,д1ʹ��
*/

#include "time_cyccnt.h"

#define  DWT_CR      *(uint32_t *)0xE0001000
#define  DWT_CYCCNT  *(uint32_t *)0xE0001004
#define  DEM_CR      *(uint32_t *)0xE000EDFC


#define  DEM_CR_TRCENA                   (1 << 24)
#define  DWT_CR_CYCCNTENA                (1 <<  0)


/* ��ʼ��ʱ��� */
void CPU_TS_TmrInit(void)
{
   /* ʹ��DWT���� */
   DEM_CR |= (uint32_t)DEM_CR_TRCENA;               

   /* DWT CYCCNT�Ĵ���������0 */
   DWT_CYCCNT = (uint32_t)0u;
        
   /* ʹ��Cortex-M3 DWT CYCCNT�Ĵ��� */
   DWT_CR |= (uint32_t)DWT_CR_CYCCNTENA;
}

uint32_t OS_TS_GET(void)
{        
   return ((uint32_t)DWT_CYCCNT);
}


