/*
 * service_temperature.h
 * create by qinsiyuan
 *			on 2016-7-25
 * �ṩ�¶ȷ���
 */
 

 #ifndef __SERVICE_TEMPERATURE_H__
 #define __SERVICE_TEMPERATURE_H__

	#include "file_service.h"

	#if TEMPERATURE_ENABLE
		
		//�¶ȷ���
		#ifndef SERVICE_GET_TEMPERATURE
			#define SERVICE_GET_TEMPERATURE	get_temperature,
		#endif

		/*
		 *	��ȡ�¶ȷ���
		 * @param ���ƶ�����
		 * @return ��ϽȨ
	 	 */
		int get_temperature(char *);
	#endif

	#ifndef SERVICE_GET_TEMPERATURE
	 	#define SERVICE_GET_TEMPERATURE 
	#endif

 #endif
 
