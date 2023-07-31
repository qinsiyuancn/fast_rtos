/*
 * file_manager.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * �ļ�������
 */
#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include "led.h"
#include "slot.h"
#include "sys_dc_12v_en.h"
#include "cpld.h"
#include "sys_nrtmen_3.h"
#include "sys_oren.h"
#include "rtm_ps.h"
#include "sys_nrtmen_12.h"
#include "temperature_selector.h"
#include "temperature.h"
#include "ttyS.h"
#include "shelf.h"
#include "rtm.h"
#include "remote_board.h"
#include "eeprom.h"

/*
 * �ļ��б�
 */
#define FILE_LIST {&file_ttyS,				\
					&file_led,				 \
					&file_slot,				  \
					&file_sys_dc_12v_en,	   \
					&file_sys_nrtmen_3,			\
					&file_sys_oren,				 \
					FILE_RTM_PS					  \
					&file_sys_nrtmen_12,		   \
					DEVICE_TEMPERATURE				\
					FILE_TEMPERATURE_SELECTOR		 \
					FILE_SHELF			   		  	  \
					FILE_REMOTE						   \
					FILE_RTM							\
					&file_eeprom,						 \
					}


/*
 * ��ѯָ�������ĵ�fd
 * �����ѯ�����е��������ܻᱻ��ʼ�������Լ�ʹ֪��fd,Ҳ������openһ��
 * @param ����(�ļ�)����
 * @param ��־
 * @return �ļ���ʾ��������ļ���ʾ����-1��ʾû�ҵ���ѯ���
 */
extern int open(const char *, int );

/*
 * �ļ�������
 * @param �ļ���ʾ��
 * @param ��ȡ�ļ�������
 * @param ��ȡ�ļ��ĳ���
 * @return ʵ�ʶ�ȡ�ĳ���
 */
extern int read(int , void *, unsigned long );

/*
 * �ļ�д����
 * @param �ļ���ʾ��
 * @param �ļ�д��������
 * @param д��ĳ���
 * @return ʵ��д��ĳ���
 */
extern int write(int , const void *, unsigned long );

/*
 * �ļ���������
 * @param �ļ���ʾ��
 * @param ���ñ�־�����������ʵ���й�
 * @param ���ò��������������ʵ���й�
 * @return
 */
extern int ioctl(int , int , void * );

/*
 * �ر��ļ�
 * @param �ļ���ʾ��
 * @return 
 */
extern int close(int );

/*
 * �����ĳ�ʼ��
 */
extern void init_files(void);

#endif
