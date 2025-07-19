/*
 * service_led.c
 * create by qinsiyuan
 *			on 2016-7-15
 * �ṩled���ط���
 */
  #include "service_led.h"

/*
 * ����led����
 * @param ָ��led�Ϳ�������
 */
void led_set(unsigned char led_order)
{
	setdata("led", &led_order, 1);
}

/*
 * 
 */
void led_red_on()
{
	led_set(led_switch(LED_RED, ENABLE));
}

/*
 * 
 */
void led_red_off()
{
	led_set(led_switch(LED_RED, DISABLE));
}

/*
 *
 */
void led_yellow_on()
{
	led_set(led_switch(LED_YELLOW, ENABLE));
}

/*
 *
 */
void led_yellow_off()
{
	led_set(led_switch(LED_YELLOW, DISABLE));
}

/*
 *
 */
void led_blue_on()
{
	led_set(led_switch(LED_BLUE, ENABLE));
}

/*
 *
 */
void led_blue_off()
{
	led_set(led_switch(LED_BLUE, DISABLE));
}

