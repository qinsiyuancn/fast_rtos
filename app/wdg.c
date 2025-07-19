 #include <LPC17xx.H>
#define WDG_COUNT	0xffffff				//  看门狗的计数值大小
int WDInit(void)
{
	LPC_WDT->WDCLKSEL &= ~(0x3);			//  时钟选择
	LPC_WDT->WDCLKSEL |= 0x80000000;		//  时钟锁定  写成 （1 << 31）会提示溢出？
	LPC_WDT->WDTC = WDG_COUNT;					//  计数值大小
	LPC_WDT->WDFEED = 0xaa;					//  设置mod寄存器前执行一次喂狗操作
	LPC_WDT->WDFEED = 0x55;	
	LPC_WDT->WDMOD |= 0x3;					//  设置寄存器模式 为 	WDEN 和 	WDRESET
	LPC_WDT->WDFEED = 0xaa;					//  进行一次喂狗操作，启动看门狗
	LPC_WDT->WDFEED = 0x55;
	return 0;
}

void FeedDog(void)
{
   	LPC_WDT->WDFEED = 0xaa;					//  进行一次喂狗操作，启动看门狗
	LPC_WDT->WDFEED = 0x55;	
}
