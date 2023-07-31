/*
 * file_service.h
 * create by qinsiyuan
 *			on 2016-7-25
 * Ϊservice���ṩ���õ��ļ�������װ
 * ����ֻ�Ƿ�װ�˳����������ļ�����
 * ֻΪ�˴��븴�ã���û�мܹ����塡
 */

 #ifndef __FILE_SERVICE_H__
 #define __FILE_SERVICE_H__

	#include "file_manager.h"

	/*
	 * ʱ�ӽṹ����
	 */
	struct clock{
		
		/*
		 * Сʱ��
		 */
		INT8U h;

		/*
		 * ������
		 */
		INT8U m;

		/*
		 * ����
		 */
		INT8U s;

		/*
		 * ������
		 */
		INT16U ms;	
	};

	/*
	 * ��װ��ȡ�ļ�����
	 * @param �ļ���
	 * @param ����
	 * @param ��������洢��������ݳ���
	 * @return ��ȡ�����ݳ���
	 */
	int getdata(const char * file_name, void * buffer, unsigned long size);

	/*
	 * ��װд���ļ�����
	 * @param �ļ���
	 * @param ����
	 * @param д�볤��
	 * @return ʵ��д�볤��
	 */
	int setdata(const char * file_name, const void * buffer, unsigned long size);
	
	/*
	 * ��װ��д�ڶ����ļ���������
	 * @param �ļ���
	 * @param ���棬��Ҫд������ݷ���
	 * @param ��Ҫд��Ŀռ䳤��
	 * @param ��������ʱ�����ж����ļ�����������
	 * @param �����С
	 * @param ��д֮����ӳ�
	 *			NULL�����ӳ�
	 * @return
	 */
	int request(const char * file_name, void * buffer, unsigned long write_size, void * msg, unsigned long read_size, const struct clock * const);
 #endif
 
