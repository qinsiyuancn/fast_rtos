/*
 * service_rtm.h
 * rtm��ط���
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
		  *	��ȡrtm��eeprom
		  * @param eeprom����ʼ��ַ
		  * @param ����eeprom����
		  * @param ��Ҫ��ȡ��eeprom�ĳ���
		  * @return ִ�н��
		  */
		int get_rtm_eeprom(unsigned short addr,char *str, unsigned long size);

		 /*
		  *	д��rtm��eeprom
		  * @param eeprom����ʼ��ַ
		  * @param д��eeprom���ݻ���
		  * @param д��eeprom�ĳ���
		  * @return ִ�н��
		  */
		int set_rtm_eeprom(unsigned short addr, char *str, unsigned char size);

		 /*
		  *	д���ַ�����rtm��eeprom
		  * @param eeprom����ʼ��ַ
		  * @param �ַ�������
		  * @return ִ�н��
		  */
		int set_rtm_eeprom_str(unsigned short addr, char *str);

		 /*
		  *	rtm�Ƿ���λ
		  * @return �Ƿ���λ
		  *			0����λ
		  *			1������λ
		  */
		unsigned char get_rtm_ps(void);

		 /*
		  *	rtm�Ȳ��֧��
		  * ��Ҫ����rtm�Ƿ���λ�����ʹ�ܺ󿨹���
		  * �Ա�֤�Ȳ��rtm���Լ�ʱ�ϵ�
		  */
		void service_rtm_power(void);

		 /*
		  *	��ȡrtm�汾��
		  * @param ���ƻ���
		  * @return ��Ͻ
		  */
		int service_get_rtm_version(char *msg);

		 /*
		  *	��ȡrtm���¶�
		  * @param ���ƻ���
		  * @return ��Ͻ
		  */
		int service_get_rtm_temperature(char *msg);

		 /*
		  *	��ȡrtm��eeprom�������
		  * @param ���ƻ���
		  * @return ��Ͻ
		  */
		int service_get_rtm_eeprom(char *msg);

		 /*
		  *	д��rtm��eeprom�������
		  * @param ���ƻ���
		  * @return ��Ͻ
		  */
		int service_set_rtm_eeprom(char *msg);

		 /*
		  *	rtm�Ƿ���λ�����
		  * @param ���ƻ���
		  * @return ��Ͻ
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



