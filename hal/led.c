/*
 * service_led.c
 * create by qinsiyuan
 *			on 2016-7-15
 */
#include "led.h"

/*
 *
 */
void led_set(const char *name, unsigned char led_order)
{
	file_write(name, &led_order, 1);
}

/*
 *
 */
void led_on(const char *name)
{
	led_set(name, 1);
}

/*
 *
 */
void led_off(const char *name)
{
	led_set(name, 0);
}

