/*
 * service_led.h
 * create by qinsiyuan
 *			on 2016-7-26
 * �ṩled���ط���
 */

 #ifndef __SERVICE_LED_H__
 #define __SERVICE_LED_H__

	#include "file_service.h"
	#define LED_RED 1
	#define LED_YELLOW 2
	#define LED_BLUE 0

	/*
	 * �ϳ�led��������
	 * @param ָ��led���
	 * @param ���ز���
	 * @return ��������
	 */
	#define led_switch(x,y) (x << 1 | y)

	/*
	 * ����led����
	 * @param ָ��led�Ϳ�������
	 */
	void led_set(unsigned char );
	void led_red_on(void);
	void led_red_off(void);
	void led_yellow_on(void);
	void led_yellow_off(void);
	void led_blue_on(void);
	void led_blue_off(void);

 #endif
 
