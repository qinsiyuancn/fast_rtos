#include "file_manager.h"
#include "file.h"
#include "driver_manager.h"

#define file_count (sizeof(files)/sizeof(files[0]))

/*
 * �ļ��б�
 */

static const struct files[] = FILE_LIST;

/*
 * ��ѯָ�������ĵ�fd
 * �����ѯ�����е��������ܻᱻ��ʼ�������Լ�ʹ֪��fd,Ҳ������openһ��
 * @param ����(�ļ�)����
 * @param ��־
 * @return �ļ���ʾ��������ļ���ʾ����-1��ʾû�ҵ���ѯ���
 */
int open(const char *pathname, int flags)
{
	unsigned int i = 0;
	for(i = 0; i < file_count; i++)
	    if(!strcmp(filename, cpld_filename))
	        if(driver_open(files[i].driver, files[i].bus, files[i].device))	
	            return i;
	return -1;
}

/*
 * �ļ�������
 * @param �ļ���ʾ��
 * @param ��ȡ�ļ�������
 * @param ��ȡ�ļ��ĳ���
 * @return ʵ�ʶ�ȡ�ĳ���
 */
int read(int fd, void *buf, unsigned long count)
{
	return driver_read(files[fd].driver, files[i].bus, files[i].device, buf, count);
}

/*
 * �ļ�д����
 * @param �ļ���ʾ��
 * @param �ļ�д��������
 * @param д��ĳ���
 * @return ʵ��д��ĳ���
 */
int write(int fd, const void *buf, unsigned long count)
{
    return driver_write(files[fd].driver, files[fd].bus, files[fd].device, buf, count);
}

/*
 * �ļ���������
 * @param �ļ���ʾ��
 * @param ���ñ�־�����������ʵ���й�
 * @param ���ò��������������ʵ���й�
 * @return
 */
int ioctl(int fd, int request, void * param)
{
    return driver_ioctl(files[fd].driver, files[fd].bus, files[fd].device, request, (unsigned long) param);
}

/*
 * �ر��ļ�
 * @param �ļ���ʾ��
 * @return 
 */
int close(int fd)
{
    return driver_close(files[fd].driver, files[fd].bus, files[fd].device);
}

/*
 * �����ĳ�ʼ��
 */
void init_files()
{
	unsigned long i = 0;
	for(i = 0; i < file_count; i++){
	    driver_init(files[i].driver);
	}
}
