/*
 * sys_nrtmen_12.c
 * create by qinsiyuan
 * 			on 2016-7-12
 * rtm 12v 上电使能
 */

 #include "sys_nrtmen_12.h"

static const char * const sys_nrtmen_12_filename = "sys_nrtmen_12";
static const struct {unsigned char port; unsigned char pos;}sys_nrtmen_12_gpio = SYS_NRTMEN_12;
static int sys_nrtmen_12_open(const char * filename, int flags)
{
	return !strcmp(filename, sys_nrtmen_12_filename);
}

static int sys_nrtmen_12_close()
{
	return 0;
}

static int sys_nrtmen_12_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf){
		set_gpio_bit_on(sys_nrtmen_12_gpio.port, sys_nrtmen_12_gpio.pos);
	}else{
		set_gpio_bit_off(sys_nrtmen_12_gpio.port, sys_nrtmen_12_gpio.pos);
	}
	return 1;
}

static void sys_nrtmen_12_init()
{
	gpio_init();
}
const struct file_operation file_sys_nrtmen_12 = {sys_nrtmen_12_init, sys_nrtmen_12_open, NULL, sys_nrtmen_12_write, NULL, sys_nrtmen_12_close};
