/*
 * sys_nrtmen_3.c
 * create by qinsiyuan
 * 			on 2016-7-12
 * RTM 3v供电使能
 */

#include "sys_nrtmen_3.h"
static const char * const sys_nrtmen_3_filename = "sys_nrtmen_3";
static const struct {unsigned char port; unsigned char pos;}sys_nrtmen_3_gpio = SYS_NRTMEN_3;
static int sys_nrtmen_3_open(const char * filename, int flags)
{
	return !strcmp(filename, sys_nrtmen_3_filename);
}

static int sys_nrtmen_3_close()
{
	return 0;
}

static int sys_nrtmen_3_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf){
		set_gpio_bit_on(sys_nrtmen_3_gpio.port, sys_nrtmen_3_gpio.pos);
	}else{
		set_gpio_bit_off(sys_nrtmen_3_gpio.port, sys_nrtmen_3_gpio.pos);
	}
	return 1;
}

static void sys_nrtmen_3_init()
{
	gpio_init();
}
const struct file_operation file_sys_nrtmen_3 = {sys_nrtmen_3_init, sys_nrtmen_3_open, NULL, sys_nrtmen_3_write, NULL, sys_nrtmen_3_close};
