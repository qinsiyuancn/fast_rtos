/*
 * cpld.c
 * create by qinsiyuan
 * 			on 2016-7-18
 * �ṩipmc��cpld�Ľ�������
 */
 #include "service_cpld.h"

 /*
  *	����cpld����
  * @param cpld����
  */
 void set_cpld_value(unsigned char v)
 {
  	setdata("cpld", &v, 1);
 }
 
 /*
  *	����cpld
  */
 void cpld_set()
 {
 	set_cpld_value(1);
 }

 /*
  *	���cpld
  */
 void cpld_clr()
 {
 	set_cpld_value(0);
 }

