/*======  ======================================================== */
#include "app.h"
#include "task_manager.h"

int main(void)
{ 
	SystemInit();


#if ENA_WDG
	WDInit();
#endif		 
	// 操作系统初始化
	OSInit();

	init_files();//初始化设备文件

	set_sys_dc_12v_en_off();
	set_sys_nrtmen_3_en_off();
	set_sys_nrtmen_12_en_off();
		
	led_blue_off();
	led_red_off();
 	led_yellow_off();

  start_tasks();
	// OS的正常运行
	OSStart();

}



