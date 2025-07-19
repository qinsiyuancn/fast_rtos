/*
 * service_led.h
 * create by qinsiyuan
 *			on 2016-7-26
 * 提供led开关服务
 */

 #ifndef __SERVICE_LED_H__
 #define __SERVICE_LED_H__

	#include "file_service.h"
	#define LED_RED 1
	#define LED_YELLOW 2
	#define LED_BLUE 0

	/*
	 * 合成led操作命令
	 * @param 指定led编号
	 * @param 开关操作
	 * @return 操作命令
	 */
	#define led_switch(x,y) (x << 1 | y)

	/*
	 * 设置led开关
	 * @param 指定led和开关命令
	 */
	void led_set(unsigned char );
	void led_red_on(void);
	void led_red_off(void);
	void led_yellow_on(void);
	void led_yellow_off(void);
	void led_blue_on(void);
	void led_blue_off(void);

 #endif
 
