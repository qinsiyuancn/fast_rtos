/*
 * service_cpld.h
 * create by qinsiyuan
 * 			on 2016-7-25
 * 提供ipmc与cpld的交互方案
 */
 
 #ifndef __SERVICE_CPLD_H__
 #define __SERVICE_CPLD_H__
 
 	#include "file_service.h"

	/*
	 * 设置cpld操作
	 * @param cpld操作
	 */
	void set_cpld_value(unsigned char);
	
	/*
	 *	设置cpld
	 */
	void cpld_set(void);

	/*
	 *	清除cpld
	 */
	void cpld_clr(void);

 #endif
