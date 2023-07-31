/*
 * file.h
 * create by qinsiyuan
 *			on 2016-7-22
 * 定义文件操作
 */

 #ifndef __FILE_H__
 #define __FILE_H__

 struct file_operation{
    void (*init)();
	int (*open)(const char *pathname, int flags);
	int (*read)(void *buf, unsigned long count);
	int (*write)(const void *buf, unsigned long count);
	int (*ioctl)(unsigned int request, unsigned long arg);
	int (*close)();
 };

 #endif
