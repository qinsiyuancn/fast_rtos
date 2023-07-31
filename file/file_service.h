/*
 * file_service.h
 * create by qinsiyuan
 *			on 2016-7-25
 * 为service层提供常用的文件操作封装
 * 函数只是封装了常见的三种文件操作
 * 只为了代码复用，并没有架构意义　
 */

 #ifndef __FILE_SERVICE_H__
 #define __FILE_SERVICE_H__

	#include "file_manager.h"

	/*
	 * 时钟结构描述
	 */
	struct clock{
		
		/*
		 * 小时数
		 */
		INT8U h;

		/*
		 * 分钟数
		 */
		INT8U m;

		/*
		 * 秒数
		 */
		INT8U s;

		/*
		 * 毫秒数
		 */
		INT16U ms;	
	};

	/*
	 * 封装读取文件过程
	 * @param 文件名
	 * @param 缓存
	 * @param 缓存允许存储的最大数据长度
	 * @return 获取的数据长度
	 */
	int getdata(const char * file_name, void * buffer, unsigned long size);

	/*
	 * 封装写入文件过程
	 * @param 文件名
	 * @param 缓存
	 * @param 写入长度
	 * @return 实际写入长度
	 */
	int setdata(const char * file_name, const void * buffer, unsigned long size);
	
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
	int request(const char * file_name, void * buffer, unsigned long write_size, void * msg, unsigned long read_size, const struct clock * const);
 #endif
 
