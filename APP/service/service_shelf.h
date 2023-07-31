/*
 * service_shelf.h
 * create by qinsiyuan
 *			on 2016-7-25
 */

 #ifndef __SERVICE_SHELF_H__
 #define __SERVICE_SHELF_H__
	#include "file_service.h"

	#if SHELF_ENABLE
		//����
		#ifndef SERVICE_GET_SLOT
			#define SERVICE_GET_SLOT get_slot_msg,
		#endif

		#ifndef SERVICE_READ_FAN
			#define SERVICE_READ_FAN read_fan,
		#endif

		#ifndef SERVICE_SET_FAN_SPEED
			#define SERVICE_SET_FAN_SPEED set_fan_speed,
		#endif

		#ifndef SERVICE_SET_FAN_REBOOT
			#define SERVICE_SET_FAN_REBOOT set_fan_reboot,
		#endif

		#ifndef SERVICE_SET_FAN_PARA
			#define SERVICE_SET_FAN_PARA set_fan_para,
		#endif

	
		#define ERR_NULL_POINTER 1
		#define ERR_NO_FAN_INDEX 2
		#define ERR_CONVERT 	 3
		#define ERR_FAN_INDEX_ILLEGAL	4
		#define ERR_NO_FAN_CMD	 5
		#define ERR_NO_CNT		 6
		#define ERR_I2C_TRANSMIT 7
		#define ERR_FORMATING_DATA 8
		#define ERR_NO_VALUE     9
	
		#define  set_crc(c) c |= 1 << 7

		/*
		 * ��ȡ��λ����
		 * @return ��λ��
		 */
		unsigned char get_slot(void);

		/*
		 * ��ȡ��λ�������
		 * @param �Ӵ��ڶ�ȡ��������ز�λ��Ϣ
		 * @return ��Ͻ
		 */
		int get_slot_msg(char * );

		/*
		 * ��ȡ������Ϣ
		 * @param ����������ط�����Ϣ
		 * @param ��Ͻ
		 */
		int read_fan(char * );

		/*
		 * ���÷����ٶ�
		 * @param �����������ִ�����
		 * @return ��Ͻ
		 */  
		int set_fan_speed(char * );

		/*
		 * �����������
		 * ͨ����������Ĭ�ϲ���
		 * @param ��������ͷ���ִ�н��
		 * @return ��Ͻ
		 */
		int set_fan_reboot(char * );

		/*
		 * ���÷���Ĭ�ϲ���
		 * ���ú󲻻�������Ч����Ҫ������������Ч
		 * @param ��������ͷ���ִ�н��
		 * @return ��Ͻ
		 */
		int set_fan_para(char * );
	#endif

	#ifndef SERVICE_GET_SLOT
		#define SERVICE_GET_SLOT
	#endif

	 #ifndef SERVICE_READ_FAN
		#define SERVICE_READ_FAN 
	 #endif
	
	 #ifndef SERVICE_SET_FAN_SPEED
		#define SERVICE_SET_FAN_SPEED
	 #endif
	
	 #ifndef SERVICE_SET_FAN_REBOOT
		#define SERVICE_SET_FAN_REBOOT
	 #endif
	
	 #ifndef SERVICE_SET_FAN_PARA
		#define SERVICE_SET_FAN_PARA
	 #endif
 #endif
 
