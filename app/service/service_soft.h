/*
 * service_soft.h
 * create by qinsiyuan
 *			on 2016-7-26
 */

 #ifndef __SERVICE_SOFT_H__
 #define __SERVICE_SOFT_H__

	#include "file_service.h"
	
	/*
	 * ���汾��
	 * ����Ӳ���޹ز��ֵİ汾��
	 */
	#define MAIN_VERSION "2016-11-8"
	
	/*
	 * ��ȡ���汾��
	 * ��Ӳ���޹صİ汾��
	 * @param ���ƻ���
	 * @return ��Ͻ
	 */
	int get_main_version(char *msg);

	/*
	 * ��ȡ�Ӱ汾��
	 * ��Ӳ����صİ汾��
	 * @param ���ƻ���
	 * @retur ��Ͻ
	 */
	int get_sub_version(char *msg);

	#if VERSION_MIX_ENABLE
	  
	  /*
	   * ��ϰ汾��
	   * ͬʱ�������汾�ź��Ӱ汾��
	   * Ϊ�˼���֮ǰ�Ŀͻ��˱���
	   * �ͻ����޸ĺ�������ؾͿ��Թص���
	   * ��������ܲ��þ�������
	   * @param ���ƻ���
	   * @return ��Ͻ
	   */
		int get_version(char *msg);
		#define SERVICE_VERSION_MIX get_version,
	#else
		#define SERVICE_VERSION_MIX
	#endif

 #endif
 
