#include "task_manager.h"
#include "service_manager.h"
#include "ucos_ii.h"
#include "cpu.h"

int main(void)
{ 
    init();
    SystemInit();
#if ENA_WDG
    WDInit();
#endif		 
    OSInit();
    init_files();

    set_sys_dc_12v_en_off();
    set_sys_nrtmen_3_en_off();
    set_sys_nrtmen_12_en_off();
	
    led_blue_off();
    led_red_off();
    led_yellow_off();

    start_tasks();
    OSStart();

}



