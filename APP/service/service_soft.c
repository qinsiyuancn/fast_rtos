/*
 * service_soft.c
 * create by qinsiyuan
 *			on 2016-7-19
 * �ṩ�������
 */
 #include "service_soft.h"

 /*
  *	���ڰ忨�޹�
  */
 static const char * const main_version = MAIN_VERSION;
 
 /*
  *	���ڰ忨���
  */
 static const char * const sub_version = SUB_VERSION;

 /*
  *	��ȡ��һ�汾��
  * ��Ϊ�����Ĺ�ͬ���ֵ���
  * @param �����ַ���
  * @param �汾�ַ���
  * @param ���ƻ���
  * @return ��Ͻ
  */
 static int get_single_version(const char * charge, const char * version, char * msg)
 {
	if(strstr(msg, charge)){
 		strcpy(msg, version);
		strcat(msg,"\r");
		return 1;
	}
 	return 0; 
 }

 /*
  *	��ȡ���汾��
  * ��Ӳ���޹صİ汾��
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int get_main_version(char *msg)
 {
	return get_single_version("read main_vers\r", main_version, msg);
 }

 /*
  *	��ȡ�Ӱ汾��
  * ��Ӳ����صİ汾��
  * @param ���ƻ���
  * @retur ��Ͻ
  */
 int get_sub_version(char *msg)
 {
	return get_single_version("read sub_vers\r", sub_version, msg);
 }


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
 int get_version(char *msg)
 {
	if(strstr(msg, "read vers\r")){
		strcpy(msg, main_version);
		strcat(msg, " ");
		strcat(msg, sub_version);
		strcat(msg, "\r");
		return 1;
	}
	return 0; 
 }
 #endif
