/*
 * file_manager.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * 文件管理器
 */
#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

/*
 * 查询指定驱动的的fd
 * 如果查询到，有的驱动可能会被初始化，所以即使知道fd,也尽量先open一下
 * @param 驱动(文件)名称
 * @param 标志
 * @return 文件标示符，如果文件标示符是-1表示没找到查询结果
 */
extern int open(const char *, int );

/*
 * 文件读操作
 * @param 文件标示符
 * @param 读取文件的内容
 * @param 读取文件的长度
 * @return 实际读取的长度
 */
extern int read(int , void *, unsigned long );

/*
 * 文件写操作
 * @param 文件标示符
 * @param 文件写操作缓存
 * @param 写入的长度
 * @return 实际写入的长度
 */
extern int write(int , const void *, unsigned long );

/*
 * 文件操作设置
 * @param 文件标示符
 * @param 设置标志，与具体驱动实现有关
 * @param 设置参数，与具体驱动实现有关
 * @return
 */
extern int ioctl(int , int , void * );

/*
 * 关闭文件
 * @param 文件标示符
 * @return 
 */
extern int close(int );

/*
 * 驱动的初始化
 */
extern void init_files(void);

#endif
