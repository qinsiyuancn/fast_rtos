/*
 * service_temperature.h
 * create by qinsiyuan
 *			on 2016-7-25
 * 提供温度服务
 */
 

 #ifndef __SERVICE_TEMPERATURE_H__
 #define __SERVICE_TEMPERATURE_H__

	#include "file_service.h"

	#if TEMPERATURE_ENABLE
		
		//温度服务
		#ifndef SERVICE_GET_TEMPERATURE
			#define SERVICE_GET_TEMPERATURE	get_temperature,
		#endif

		/*
		 *	获取温度服务
		 * @param 控制端命令
		 * @return 管辖权
	 	 */
		int get_temperature(char *);
	#endif

	#ifndef SERVICE_GET_TEMPERATURE
	 	#define SERVICE_GET_TEMPERATURE 
	#endif

 #endif
 
