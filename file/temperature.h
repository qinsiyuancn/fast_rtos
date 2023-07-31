/*
 * temperature.h
 * 温度传感器管理文件
 * 如果温度传感器更换文件，需要在这里添加描述
 */

 #ifndef __TEMPERATURE_H__
 #define __TEMPERATURE_H__

	#if TEMPERATURE_ENABLE
		//传感器列表

		#if DEVICE_TMC435
			#include "temperature_tmc435.h"
			#ifndef DEVICE_TEMPERATURE
				#define DEVICE_TEMPERATURE &file_temperature_tmc435,
			#endif
		#endif

	#endif

	//定义文件默认值
 	#ifndef DEVICE_TEMPERATURE
			#define DEVICE_TEMPERATURE
	#endif

 #endif

