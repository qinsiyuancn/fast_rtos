/*
 * sys_dc_12v_en.c
 * create by qinsiyuan
 * 			on 2016-7-12
 *	给前卡上电
 */
 #include "sys_dc_12v_en.h"

static const char * const sys_dc_12v_en_filename = "sys_dc_12v_en";
static const struct {unsigned char port; unsigned char pos;}sys_dc_12v_en_gpio = SYS_DC_12V_EN;
static int sys_dc_12v_en_open(const char * filename, int flags)
{
	return !strcmp(filename, sys_dc_12v_en_filename);
}

static int sys_dc_12v_en_close()
{
	return 0;
}


static int sys_dc_12v_en_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	if(*(unsigned char*)buf){
		set_gpio_bit_on(sys_dc_12v_en_gpio.port, sys_dc_12v_en_gpio.pos);
	}else{
		set_gpio_bit_off(sys_dc_12v_en_gpio.port, sys_dc_12v_en_gpio.pos);
	}
	return 1;
}

static void sys_dc_12v_en_init()
{
	gpio_init();
}

const struct file_operation file_sys_dc_12v_en = {sys_dc_12v_en_init, sys_dc_12v_en_open, NULL, sys_dc_12v_en_write, NULL, sys_dc_12v_en_close};
