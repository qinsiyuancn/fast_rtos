/*
 * file.h
 * create by qinsiyuan
 *			on 2016-7-22
 * 定义文件操作
 */

 #ifndef __DRIVER_H__
 #define __DRIVER_H__

 struct file_operation{
    void (*init)();
	int (*open)(unsigned int bus, unsigned int dev);
	int (*read)(unsigned int bus, unsigned int dev, void *buf, unsigned long count);
	int (*write)(unsigned int bus, unsigned int dev, const void *buf, unsigned long count);
	int (*ioctl)(unsigned int bus, unsigned int dev, unsigned int request, unsigned long arg);
	int (*close)(unsigned int bus, unsigned int dev);
 };

typedef struct driver {
    const char * const name;
    const struct file_operation fops;
} driver;

 #endif
