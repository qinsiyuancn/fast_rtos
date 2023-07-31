/*
 * file_service.c
 * create by qinsiyuan
 * 			on 2016-7-15
 * 封装file的io操作
 * 常用的有只写，只读和写读三种
 * 函数只是封装了常见的三种文件操作
 * 只为了代码复用，并没有架构意义
 */

 #include "file_service.h"

/*
 * 封装读取文件过程
 * @param 文件名
 * @param 缓存
 * @param 缓存允许存储的最大数据长度
 * @return 获取的数据长度
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
  * 封装写入文件过程
  * @param 文件名
  * @param 缓存
  * @param 写入长度
  * @return 实际写入长度
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
  * 封装先写在读的文件操作过程
  * @param 文件名
  * @param 缓存，将要写入的内容放入
  * @param 将要写入的空间长度
  * @param 函数返回时将从中读出文件反馈的内容
  * @param 缓存大小
  * @param 读写之间的延迟
  *			NULL：不延迟
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
