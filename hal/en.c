/*
 * service_en.c
 * create by qinsiyuan
 * 			on 2016-7-18
 * 提供电源使能服务
 */

 #include "service_en.h"

 /*
  *	设置使能操作
  * @param 设备名称
  * @param 使能操作
  */
 void set_en(const char *service, unsigned char en_switch)
 {
	setdata(service, &en_switch, 1); 	
 }

 /*
  *	设置全局12V上电
  * @param 使能操作
  */
 void set_sys_dc_12v_en(unsigned char sys_dc_12v_en_switch)
 {
 	set_en("sys_dc_12v_en", sys_dc_12v_en_switch);
 }

 /*
  *	设置全局12V上电
  */
 void set_sys_dc_12v_en_on()
 {
	set_sys_dc_12v_en(sys_dc_12v_en_on); 	
 }

 /*
  * 设置全局12V下电
  */
 void set_sys_dc_12v_en_off()
 {
 	set_sys_dc_12v_en(sys_dc_12v_en_off);
 }

 /*
  *	设置后卡3V上电操作
  * @param 上电使能操作
  */
 void set_sys_nrtmen_3_en(unsigned char sys_nrtmen_3_en_switch)
 {
 	set_en("sys_nrtmen_3", sys_nrtmen_3_en_switch);
 }

 /*
  *	设置后卡3V上电
  */
 void set_sys_nrtmen_3_en_on()
 {
	set_sys_nrtmen_3_en(sys_nrtmen_3_en_on); 	
 }

 /*
  *	设置后卡3V下电
  */
 void set_sys_nrtmen_3_en_off()
 {
 	set_sys_nrtmen_3_en(sys_nrtmen_3_en_off);
 }

 /*
  *	设置后卡12V上电操作
  * @param 后卡上电操作
  */
 void set_sys_nrtmen_12_en(unsigned char sys_nrtmen_12_en_switch)
 {
 	set_en("sys_nrtmen_12", sys_nrtmen_12_en_switch);
 }

 /*
  *	后卡12V上电使能
  */
 void set_sys_nrtmen_12_en_on()
 {
	set_sys_nrtmen_12_en(sys_nrtmen_12_en_on); 	
 }

 /*
  *	关闭后卡12V上电使能
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

