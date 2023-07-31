/*
 * file_service.c
 * create by qinsiyuan
 * 			on 2016-7-15
 * ��װfile��io����
 * ���õ���ֻд��ֻ����д������
 * ����ֻ�Ƿ�װ�˳����������ļ�����
 * ֻΪ�˴��븴�ã���û�мܹ�����
 */

 #include "file_service.h"

/*
 * ��װ��ȡ�ļ�����
 * @param �ļ���
 * @param ����
 * @param ��������洢��������ݳ���
 * @return ��ȡ�����ݳ���
 */
 int getdata(const char * file_name, void * buffer, unsigned long size){
 	int ret = 0;
	int fd = open(file_name, 0);
	if(fd >= 0){
		ret = read(fd, buffer, size);
		close(fd);
	}
	return ret;
 }

 /*
  * ��װд���ļ�����
  * @param �ļ���
  * @param ����
  * @param д�볤��
  * @return ʵ��д�볤��
  */
 int setdata(const char * file_name, const void * buffer, unsigned long size){
 	int ret = 0;
	int fd = open(file_name, 0);
	if(fd >= 0){
		ret = write(fd, buffer, size);
		close(fd);
	}
	return ret;
 }

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
 int request(const char * file_name, void * buffer, unsigned long write_size, void * msg, unsigned long read_size, const struct clock * const delay_time )
 {
 	int ret = 0;
	int fd = open(file_name, 0);
	if(fd >= 0){
		ret = write(fd, buffer, write_size);
		if(ret > 0){
			if(delay_time)OSTimeDlyHMSM(delay_time->h, delay_time->m, delay_time->s, delay_time->ms);
			ret = read(fd, msg, read_size);
		}
		close(fd);
	}
	return ret;	
 }
