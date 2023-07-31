#include "file_manager.h"

#define file_count (sizeof(files)/sizeof(files[0]))

#define check_fd(fd) do{if(fd < 0) return -1;if(fd >= file_count) return -1;}while(0)

/*
 * �ļ��б�
 */
static const struct file_operation * const files[] = FILE_LIST;

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
	for(i = 0; i < file_count; i++){
		if(files[i])
			if(files[i]->open)
				if(files[i]->open(pathname, flags))
					return i;
	}
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
	check_fd(fd);
	if(files[fd])
		if(files[fd]->read)
			return(files[fd]->read(buf, count));
	return -1;
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
	check_fd(fd);
	if(files[fd])
		if(files[fd]->write)
			return(files[fd]->write(buf, count));
	return -1;
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
	check_fd(fd);
	if(files[fd])
		if(files[fd]->ioctl)
			return(files[fd]->ioctl(request, (unsigned long) param));
	return -1;
}

/*
 * �ر��ļ�
 * @param �ļ���ʾ��
 * @return 
 */
int close(int fd)
{
	check_fd(fd);
	if(files[fd])
		if(files[fd]->close)
			return(files[fd]->close());
	return -1;
}

/*
 * �����ĳ�ʼ��
 */
void init_files()
{
	unsigned long i = 0;
	for(i = 0; i < file_count; i++){
		if(files[i])
			if(files[i]->init)
				files[i]->init();
	}
}
