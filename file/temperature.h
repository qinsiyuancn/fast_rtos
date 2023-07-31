/*
 * temperature.h
 * �¶ȴ����������ļ�
 * ����¶ȴ����������ļ�����Ҫ�������������
 */

 #ifndef __TEMPERATURE_H__
 #define __TEMPERATURE_H__

	#if TEMPERATURE_ENABLE
		//�������б�

		#if DEVICE_TMC435
			#include "temperature_tmc435.h"
			#ifndef DEVICE_TEMPERATURE
				#define DEVICE_TEMPERATURE &file_temperature_tmc435,
			#endif
		#endif

	#endif

	//�����ļ�Ĭ��ֵ
 	#ifndef DEVICE_TEMPERATURE
			#define DEVICE_TEMPERATURE
	#endif

 #endif

