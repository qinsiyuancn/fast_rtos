/*
 * service_cpld.h
 * create by qinsiyuan
 * 			on 2016-7-25
 * �ṩipmc��cpld�Ľ�������
 */
 
 #ifndef __SERVICE_CPLD_H__
 #define __SERVICE_CPLD_H__
 
 	#include "file_service.h"

	/*
	 * ����cpld����
	 * @param cpld����
	 */
	void set_cpld_value(unsigned char);
	
	/*
	 *	����cpld
	 */
	void cpld_set(void);

	/*
	 *	���cpld
	 */
	void cpld_clr(void);

 #endif
