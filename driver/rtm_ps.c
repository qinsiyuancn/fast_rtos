/* 
 * rtm_ps.c
 * create by qinsiyuan
 * 			on 2016-7-12
 * ≈–∂œrtm «∑Ò‘⁄Œª
 */

#include "rtm_ps.h"

#if RTM_SUPPORT
static const char * const rtm_ps_filename = "rtm_ps";
static const struct {unsigned char port; unsigned char pos;}rtm_ps_gpio = RTM_PS;
static int rtm_ps_open(const char * filename, int flags)
{
	return !strcmp(filename, rtm_ps_filename);
}

static int rtm_ps_close()
{
	return 0;
}

static int rtm_ps_read(void *buf, unsigned long count)
{
	if(buf){
		if(count){
			*(unsigned char *)buf = get_gpio_bit(rtm_ps_gpio.port, rtm_ps_gpio.pos); 
			return 1;
		}
	}
	return 0;
}

static void rtm_ps_init()
{
	gpio_init();
}
const struct file_operation file_rtm_ps = {rtm_ps_init, rtm_ps_open, rtm_ps_read, NULL, NULL, rtm_ps_close};
#endif
