 #include <LPC17xx.H>
#define WDG_COUNT	0xffffff				//  ���Ź��ļ���ֵ��С
int WDInit(void)
{
	LPC_WDT->WDCLKSEL &= ~(0x3);			//  ʱ��ѡ��
	LPC_WDT->WDCLKSEL |= 0x80000000;		//  ʱ������  д�� ��1 << 31������ʾ�����
	LPC_WDT->WDTC = WDG_COUNT;					//  ����ֵ��С
	LPC_WDT->WDFEED = 0xaa;					//  ����mod�Ĵ���ǰִ��һ��ι������
	LPC_WDT->WDFEED = 0x55;	
	LPC_WDT->WDMOD |= 0x3;					//  ���üĴ���ģʽ Ϊ 	WDEN �� 	WDRESET
	LPC_WDT->WDFEED = 0xaa;					//  ����һ��ι���������������Ź�
	LPC_WDT->WDFEED = 0x55;
	return 0;
}

void FeedDog(void)
{
   	LPC_WDT->WDFEED = 0xaa;					//  ����һ��ι���������������Ź�
	LPC_WDT->WDFEED = 0x55;	
}
