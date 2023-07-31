#include "file_manager.h"

#define file_count (sizeof(files)/sizeof(files[0]))

#define check_fd(fd) do{if(fd < 0) return -1;if(fd >= file_count) return -1;}while(0)

/*
 * 文件列表
 */
static const struct file_operation * const files[] = FILE_LIST;

/*
 * 查询指定驱动的的fd
 * 如果查询到，有的驱动可能会被初始化，所以即使知道fd,也尽量先open一下
 * @param 驱动(文件)名称
 * @param 标志
 * @return 文件标示符，如果文件标示符是-1表示没找到查询结果
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
 * 文件读操作
 * @param 文件标示符
 * @param 读取文件的内容
 * @param 读取文件的长度
 * @return 实际读取的长度
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
 * 文件写操作
 * @param 文件标示符
 * @param 文件写操作缓存
 * @param 写入的长度
 * @return 实际写入的长度
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
 * 文件操作设置
 * @param 文件标示符
 * @param 设置标志，与具体驱动实现有关
 * @param 设置参数，与具体驱动实现有关
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
 * 关闭文件
 * @param 文件标示符
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
 * 驱动的初始化
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
