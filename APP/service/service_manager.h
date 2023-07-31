/*
 * service_manager.h
 * create by qinsiyuan
 *			on 2016-7-19
 * �ṩ��service�ķ������
 * ���з�����Ҫͨ����ͷ�ļ�����service_manager.h����ע��
 * service��Ϊ�������ڷ���
 * �ڷ���:
 *	1.Ϊ�ϲ�Ӧ��ֱ���ṩ���ýӿ�
 *	2.�ӿ����⣬����ʹ�÷������ɶ���
 *	3.�������ֱ�ӵ��ú������Ƽ���
 * �����
 *	1.�ṩԶ�̷���
 *	2.�ӿڹ̶�����Ϊ��int (*out_service)(char * msg)
 *  3.ע�������Ҫͷ�ļ�������Ҫ���������Ƽ���SERVICE_LIST
 *  4.���ڿ����ò����ķ������Ĭ��ֵ�Σգ̣�
 */

 #ifndef __SERVICE_MANAGER_H__
 #define __SERVICE_MANAGER_H__

 #include "service_led.h"
 #include "service_temperature.h"
 #include "service_en.h"
 #include "service_cpld.h"
 #include "service_shelf.h"
 #include "service_soft.h"
 #include "service_rtm.h"
 #include "service_board.h"
 #include "service_eeprom.h"

 /*
  *	�ⲿ��������
  * �ṩԶ�̷���
  * ���ô�������ģʽ
  * 0	û�й�ϽȨ��������һ��������
  * ��0	ӵ�й�ϽȨ����ȫ�����������ֱ�ӷ��أ����ٴ��ݸ���һ������
  * @param ��������
  * @return �������Σ���ϽȨ��
  */
 typedef int (*out_service)(char * msg);
					 
 /*
  *	������б�
  */
 #define SERVICE_LIST {        \
 	SERVICE_GET_TEMPERATURE     \
 	SERVICE_GET_SLOT		     \
 	SERVICE_READ_FAN 	  		  \
 	SERVICE_SET_FAN_SPEED		   \
	SERVICE_SET_FAN_REBOOT			\
	SERVICE_SET_FAN_PARA			 \
	get_main_version,				  \
	get_sub_version,				   \
	SERVICE_VERSION_MIX					\
	SERVICE_GET_RTM_VERSION				 \
	SERVICE_GET_RTM_TEMPERATURE			  \
	SERVICE_GET_RTM_EEPROM				   \
	SERVICE_SET_RTM_EEPROM					\
	SERVICE_GET_RTM_PS						 \
	SERVICE_BOARD_POWER_ON					  \
	SERVICE_BOARD_POWER_OFF					   \
	service_eeprom_read,						\
	service_eeprom_write,						 \
 }

/*
 * �ṩ�ض�������Ч�Լ������ϽȨ
 * @param ָ������
 * @param �������
 */
int request_service(unsigned long , char *);

/*
 * ��ѵ���ṩ�ķ���
 * @param �������
 */
int request_service_duty(char * msg);

 #endif
