/*
 * algorithm_queue.h
 * create by qinsiyuan
 *			on 2016-7-26
 * 队列结构封装
 */

 #ifndef __ALGORITHM_QUEUE_H__
 #define __ALGORITHM_QUEUE_H__

	#include "ucos_ii.h"
	#include <string.h>
	#include <stdlib.h>

 /*
  *	队列结构
  */
 typedef struct{
 	
	/*
	 * 队列成员数
	 */
 	unsigned long size;
	
	/*
	 * 单个成员占用的空间
	 */
	unsigned long unit;

	/*
	 * 队里存储区指针
	 */
 	char * queue;

	/*
	 * 队列头索引
	 */
	unsigned long head;

	/*
	 * 队列头长度
	 */
	unsigned long length;

	/*
	 * 互斥访问控制
	 */
	OS_EVENT  * use_mutex;
 } calc_queue;
  
 /*
  *	创建队列
  * @param 单位空间
  * @param 队列成员数量
  * @return 队列结构
  */
  calc_queue * queue_create(unsigned long , unsigned long );

 /*
  *	删除队列
  * @param 队列结构
  */
  void queue_delete(calc_queue *);
  
 /*
  *	出队
  * @param 队列结构
  * @param 出队成员
  * @return 执行结果
  *			0：失败
  *			1：成功
  */
  unsigned char poll(calc_queue *, void * );

 /*
  *	入队
  * @param
  * @param
  * @return 
  */
  unsigned char offer(calc_queue *, const void * );

 /*
  *	获取队列长度
  * @param 队列结构
  * @return 队列长度
  */
  unsigned long queue_length(const calc_queue * const );

 /*
  *	清空队列
  * @param 队列结构
  * @param 队列保存缓冲区
  *			NULL：不保存队列内容，直接清空队列
  * @param 缓冲区size
  *			0:不保存队列内容，直接清空队列
  * @return 保存的队列内容的size
  */
  unsigned long queue_clean(calc_queue *queue, void * , unsigned long );

 #endif
