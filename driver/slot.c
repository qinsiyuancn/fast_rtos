/*
 * slot.c
 * create by qinsiyuan
 * 			on 2016-7-11
 * ≤€Œª∫≈
 */

#include "slot.h"

static const char * const slot_filename = "slot";
static const struct {const struct {const unsigned char port; const unsigned char pos;}enable;
const struct {const unsigned char port; const unsigned char pos; const unsigned char mask;}slot;} slot_gpio = BOARD_SLOT;
static int slot_open(const char * filename, int flags)
{
	if(strcmp(filename, slot_filename))return 0;
		set_gpio_bit_off(slot_gpio.enable.port, slot_gpio.enable.pos);
	return 1;
}

static int slot_close()
{
	return 0;
}

static int slot_read(void *buf, unsigned long count)
{
	unsigned char slot = 0, i = 0;
	if(!buf)return 0;
	if(!count)return 0;
	slot = (unsigned char )get_gpio_bits(slot_gpio.slot.port, slot_gpio.slot.mask, slot_gpio.slot.pos); 
	for(i = 0; i < 8; i++){
		*(unsigned char *)buf = (*(unsigned char *)buf << 1) | (slot & 1);
		slot >>= 1;
	}
	*(unsigned char *)buf &= 0x7f;
	return 1;
}

static void slot_init()
{
	gpio_init();
}
const struct file_operation file_slot = {slot_init, slot_open, slot_read, NULL, NULL, slot_close};
