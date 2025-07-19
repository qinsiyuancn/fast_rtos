/*
 * service_led.c
 * create by qinsiyuan
 *			on 2016-7-15
 * 提供led开关服务
 */
  #include "service_led.h"

/*
 * 设置led开关
 * @param 指定led和开关命令
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

