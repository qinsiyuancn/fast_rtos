/*======  ======================================================== */
#include "app.h"
#include "task_manager.h"

int main(void)
{ 
	SystemInit();


#if ENA_WDG
	WDInit();
#endif		 
	// ����ϵͳ��ʼ��
	OSInit();

	init_files();//��ʼ���豸�ļ�

	set_sys_dc_12v_en_off();
	set_sys_nrtmen_3_en_off();
	set_sys_nrtmen_12_en_off();
		
	led_blue_off();
	led_red_off();
 	led_yellow_off();

  start_tasks();
	// OS����������
	OSStart();

}



