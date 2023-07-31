/*
 * service_en.c
 * create by qinsiyuan
 * 			on 2016-7-18
 * �ṩ��Դʹ�ܷ���
 */

 #include "service_en.h"

 /*
  *	����ʹ�ܲ���
  * @param �豸����
  * @param ʹ�ܲ���
  */
 void set_en(const char *service, unsigned char en_switch)
 {
	setdata(service, &en_switch, 1); 	
 }

 /*
  *	����ȫ��12V�ϵ�
  * @param ʹ�ܲ���
  */
 void set_sys_dc_12v_en(unsigned char sys_dc_12v_en_switch)
 {
 	set_en("sys_dc_12v_en", sys_dc_12v_en_switch);
 }

 /*
  *	����ȫ��12V�ϵ�
  */
 void set_sys_dc_12v_en_on()
 {
	set_sys_dc_12v_en(sys_dc_12v_en_on); 	
 }

 /*
  * ����ȫ��12V�µ�
  */
 void set_sys_dc_12v_en_off()
 {
 	set_sys_dc_12v_en(sys_dc_12v_en_off);
 }

 /*
  *	���ú�3V�ϵ����
  * @param �ϵ�ʹ�ܲ���
  */
 void set_sys_nrtmen_3_en(unsigned char sys_nrtmen_3_en_switch)
 {
 	set_en("sys_nrtmen_3", sys_nrtmen_3_en_switch);
 }

 /*
  *	���ú�3V�ϵ�
  */
 void set_sys_nrtmen_3_en_on()
 {
	set_sys_nrtmen_3_en(sys_nrtmen_3_en_on); 	
 }

 /*
  *	���ú�3V�µ�
  */
 void set_sys_nrtmen_3_en_off()
 {
 	set_sys_nrtmen_3_en(sys_nrtmen_3_en_off);
 }

 /*
  *	���ú�12V�ϵ����
  * @param ���ϵ����
  */
 void set_sys_nrtmen_12_en(unsigned char sys_nrtmen_12_en_switch)
 {
 	set_en("sys_nrtmen_12", sys_nrtmen_12_en_switch);
 }

 /*
  *	��12V�ϵ�ʹ��
  */
 void set_sys_nrtmen_12_en_on()
 {
	set_sys_nrtmen_12_en(sys_nrtmen_12_en_on); 	
 }

 /*
  *	�رպ�12V�ϵ�ʹ��
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

