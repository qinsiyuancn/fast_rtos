/*
 * service_rtm.h
 * rtm相关服务
 *
 */
 
 #ifndef __SERVICE_RTM_H__
 #define __SERVICE_RTM_H__
 	
	#include "file_service.h"
	#include "service_en.h"
	#include "service_cpld.h"
	
	#if RTM_SUPPORT
	
		#ifndef SERVICE_GET_RTM_VERSION
			#define SERVICE_GET_RTM_VERSION service_get_rtm_version,
		#endif
		#ifndef SERVICE_GET_RTM_TEMPERATURE
			#define SERVICE_GET_RTM_TEMPERATURE service_get_rtm_temperature,
		#endif
		#ifndef SERVICE_GET_RTM_EEPROM
			#define SERVICE_GET_RTM_EEPROM service_get_rtm_eeprom,
		#endif
		#ifndef SERVICE_SET_RTM_EEPROM
			#define SERVICE_SET_RTM_EEPROM service_set_rtm_eeprom,
		#endif
		#ifndef	SERVICE_GET_RTM_PS
			#define	SERVICE_GET_RTM_PS service_get_rtm_ps,
		#endif

		 /*
		  *	获取rtm的eeprom
		  * @param eeprom的起始地址
		  * @param 返回eeprom缓存
		  * @param 需要获取的eeprom的长度
		  * @return 执行结果
		  */
		int get_rtm_eeprom(unsigned short addr,char *str, unsigned long size);

		 /*
		  *	写入rtm的eeprom
		  * @param eeprom的起始地址
		  * @param 写入eeprom内容缓存
		  * @param 写入eeprom的长度
		  * @return 执行结果
		  */
		int set_rtm_eeprom(unsigned short addr, char *str, unsigned char size);

		 /*
		  *	写入字符串到rtm的eeprom
		  * @param eeprom的起始地址
		  * @param 字符串缓存
		  * @return 执行结果
		  */
		int set_rtm_eeprom_str(unsigned short addr, char *str);

		 /*
		  *	rtm是否在位
		  * @return 是否在位
		  *			0：在位
		  *			1：不在位
		  */
		unsigned char get_rtm_ps(void);

		 /*
		  *	rtm热插拔支持
		  * 需要根据rtm是否在位的情况使能后卡供电
		  * 以保证热插拔rtm可以及时上电
		  */
		void service_rtm_power(void);

		 /*
		  *	获取rtm版本号
		  * @param 控制缓存
		  * @return 管辖
		  */
		int service_get_rtm_version(char *msg);

		 /*
		  *	获取rtm的温度
		  * @param 控制缓存
		  * @return 管辖
		  */
		int service_get_rtm_temperature(char *msg);

		 /*
		  *	获取rtm的eeprom的外服务
		  * @param 控制缓存
		  * @return 管辖
		  */
		int service_get_rtm_eeprom(char *msg);

		 /*
		  *	写入rtm的eeprom的外服务
		  * @param 控制缓存
		  * @return 管辖
		  */
		int service_set_rtm_eeprom(char *msg);

		 /*
		  *	rtm是否在位外服务
		  * @param 控制缓存
		  * @return 管辖
		  */
		int service_get_rtm_ps(char * msg);

	#endif

	#ifndef SERVICE_GET_RTM_VERSION
		#define SERVICE_GET_RTM_VERSION 
	#endif
	#ifndef SERVICE_GET_RTM_TEMPERATURE
		#define SERVICE_GET_RTM_TEMPERATURE 
	#endif
	#ifndef SERVICE_GET_RTM_EEPROM
		#define SERVICE_GET_RTM_EEPROM 
	#endif
	#ifndef SERVICE_SET_RTM_EEPROM
		#define SERVICE_SET_RTM_EEPROM 
	#endif
	#ifndef SERVICE_GET_RTM_PS
		#define SERVICE_GET_RTM_PS
	#endif

 #endif



