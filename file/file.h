/*
 * file.h
 * create by qinsiyuan
 *			on 2016-7-22
 * 定义文件操作
 */

 #ifndef __FILE_H__
 #define __FILE_H__

typedef struct file
{
    const char * const name;
    const unsigned int device;
    const unsigned int driver;
    const unsigned int bus;
} file;

 #endif
