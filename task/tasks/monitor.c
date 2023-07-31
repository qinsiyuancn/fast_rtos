#include "monitor.h"

static 	 OS_STK stack[64]; 

/*
 * 轮训操作
 */
static void fun(void *p_arg)
{
	unsigned char count1 = 5;
	OS_CPU_SysTickInit();
	while(count1--) {
		led_blue_on();
		OSTimeDlyHMSM(0, 0, 0, 900);
		led_blue_off();
		OSTimeDlyHMSM(0, 0, 0, 100);
	}
	set_sys_dc_12v_en_on();
	led_blue_off();
	led_yellow_on();
	OSTimeDlyHMSM(0, 0, 3, 0);		
	while(1){
		//监控
		#if RTM_SUPPORT	
			service_rtm_power();
		#endif
		//监控把手，不用中断了，轮训吧，挺好,本来之前就是中断加轮训,改变全局变量，不如直接读gpio状态...

		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

static const struct Task task = {fun, {stack, (sizeof(stack)/sizeof(stack[0]))}};
const struct Task * const monitor = &task;