/*
 * led.c
 * create by qinsiyuan
 *			on 2016-7-8
 * ledÇý¶¯
 */
 #include "led.h"
static const char * const led_filename = "led";
static const struct {unsigned char port; unsigned char pos;} led_gpio[] = BOARD_GPIO_LED;
static int led_open(const char * filename, int flags)
{
	return !strcmp(filename, led_filename);
}

static int led_close()
{
	return 0;
}

static int led_read(void *buf, unsigned long count)
{
	unsigned char leds = 0, i = 0;
	if(!buf)return 0;
	if(!count)return 0;
	for(i = 0; i < sizeof(led_gpio)/sizeof(led_gpio[0]) && i < count; i++){
		leds = leds << 1 | get_gpio_bit(led_gpio[i].port, led_gpio[i].pos);
	}
	*(unsigned char *)buf = leds; 
	return 1;
}

static int led_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf & 0x1) {
		set_gpio_bit_on(led_gpio[*(unsigned char*)buf >> 1].port, led_gpio[*(unsigned char*)buf >> 1].pos);
	}else{
		set_gpio_bit_off(led_gpio[*(unsigned char*)buf >> 1].port, led_gpio[*(unsigned char*)buf >> 1].pos);
	}
	return 1;
}

static void led_init()
{
	gpio_init();
}

const struct file_operation file_led = {led_init, led_open, led_read, led_write, NULL, led_close};
