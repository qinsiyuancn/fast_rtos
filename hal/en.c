/*
 * service_en.c
 * create by qinsiyuan
 * 			on 2016-7-18
 */

#include "service_en.h"

/*
 *
 */
void set_en(const char *service, unsigned char en_switch)
{
    file_write(service, &en_switch, 1); 	
}

/*
 *
 */
void set_sys_dc_12v_en(unsigned char sys_dc_12v_en_switch)
{
    set_en("sys_dc_12v_en", sys_dc_12v_en_switch);
}

/*
 *
 */
void set_sys_dc_12v_en_on()
{
    set_sys_dc_12v_en(sys_dc_12v_en_on); 	
}

/*
 *
 */
void set_sys_dc_12v_en_off()
{
    set_sys_dc_12v_en(sys_dc_12v_en_off);
}

/*
 *
 */
void set_sys_nrtmen_3_en(unsigned char sys_nrtmen_3_en_switch)
{
    set_en("sys_nrtmen_3", sys_nrtmen_3_en_switch);
}

/*
 *
 */
void set_sys_nrtmen_3_en_on()
{
    set_sys_nrtmen_3_en(sys_nrtmen_3_en_on); 	
}

/*
 *
 */
void set_sys_nrtmen_3_en_off()
{
    set_sys_nrtmen_3_en(sys_nrtmen_3_en_off);
}

/*
 *
 */
void set_sys_nrtmen_12_en(unsigned char sys_nrtmen_12_en_switch)
{
    set_en("sys_nrtmen_12", sys_nrtmen_12_en_switch);
}

/*
 *
 */
void set_sys_nrtmen_12_en_on()
{
    set_sys_nrtmen_12_en(sys_nrtmen_12_en_on); 	
}

/*
 *
 */
void set_sys_nrtmen_12_en_off()
{
    set_sys_nrtmen_12_en(sys_nrtmen_12_en_off);
}

void set_sys_oren(unsigned char sys_nrtmen_12_en_switch)
{
    set_en("sys_oren", sys_nrtmen_12_en_switch);
}

void set_sys_oren_on()
{
    set_sys_oren(sys_oren_on); 	
}

void set_sys_oren_off()
{
    set_sys_oren(sys_oren_off);
}

