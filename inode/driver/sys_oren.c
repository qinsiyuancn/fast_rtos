/*
 * sys_oren.c
 * create by qinsiyuan
 * 			on 2016-7-12
 */

 #include "sys_oren.h"

static const char * const sys_oren_filename = "sys_oren";
static const struct {unsigned char port; unsigned char pos;}sys_oren_gpio = SYS_OREN;
static int sys_oren_open(const char * filename, int flags)
{
	return !strcmp(filename, sys_oren_filename);
}

static int sys_oren_close()
{
	return 0;
}

static int sys_oren_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf){
		set_gpio_bit_on(sys_oren_gpio.port, sys_oren_gpio.pos);
	}else{
		set_gpio_bit_off(sys_oren_gpio.port, sys_oren_gpio.pos);
	}
	return 1;
}

static void sys_oren_init()
{
	gpio_init();
}
const struct file_operation file_sys_oren = {sys_oren_init, sys_oren_open, NULL, sys_oren_write, NULL, sys_oren_close};
