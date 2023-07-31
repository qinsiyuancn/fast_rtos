/*
 * cpld.c
 * create by qinsiyuan
 * 			on 2016-7-18
 * 提供ipmc与cpld的交互方案
 */
 #include "service_cpld.h"

 /*
  *	设置cpld操作
  * @param cpld操作
  */
 void set_cpld_value(unsigned char v)
 {
  	setdata("cpld", &v, 1);
 }
 
 /*
  *	设置cpld
  */
 void cpld_set()
 {
 	set_cpld_value(1);
 }

 /*
  *	清除cpld
  */
 void cpld_clr()
 {
 	set_cpld_value(0);
 }

