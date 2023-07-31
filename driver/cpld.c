/*
 * cpld.c
 * create by qinsiyuan
 * 			on 2016-7-12
 * 通知cpld rtm在位情况
 */
 #include "cpld.h"

static const char * const cpld_filename = "cpld";
static const struct {unsigned char port; unsigned char pos;}cpld_gpio = CPLD_PS;
static int cpld_open(const char * filename, int flags)
{
	return !strcmp(filename, cpld_filename);
}

static int cpld_close()
{
	return 0;
}

static int cpld_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf){
		set_gpio_bit_on(cpld_gpio.port, cpld_gpio.pos);
	}else{
		set_gpio_bit_off(cpld_gpio.port, cpld_gpio.pos);
	}
	return 1;
}

static void cpld_init()
{
	gpio_init();
}
const struct file_operation file_cpld = {cpld_init, cpld_open, NULL, cpld_write, NULL, cpld_close};
