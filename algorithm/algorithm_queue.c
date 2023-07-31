/*
 * algorithm_queue.c
 * create by qinsiyuan
 *			on 2016-7-13
 * 队列结构封装
 */
 #include "algorithm_queue.h"

 /*
  *	创建队列
  * @param 单位空间
  * @param 队列成员数量
  * @return 队列结构
  */
 calc_queue * queue_create(unsigned long unit, unsigned long size)
 {
 	INT8U mutex_error = 0;
 	calc_queue * queue = (calc_queue *)malloc(sizeof(calc_queue));
	if(queue){
		memset(queue, 0, sizeof(calc_queue));
		queue->size = size;
		queue->unit = unit;
		queue->queue = (char *)malloc(unit * size);
		if(!queue->queue){
			free(queue);
			queue = NULL;	
		}
		queue->use_mutex = OSMutexCreate(1, &mutex_error);
	}
	return queue;
 }

 /*
  *	删除队列
  * @param 队列结构
  */
 void queue_delete(calc_queue *queue)
 {
 	INT8U mutex_error = 0;
 	if(!queue)return;
	OSMutexDel (queue->use_mutex, 0, &mutex_error);
	if(queue->queue)free(queue->queue);
	free(queue);
 }

 /*
  *	出队
  * @param 队列结构
  * @param 出队成员
  * @return 执行结果
  *			0：失败
  *			1：成功
  */
 unsigned char poll(calc_queue *queue, void * ret)
 {
 	INT8U mutex_error = 0;
 	if(queue){
		if(queue->queue){
			if(queue->length){
				if(ret){
					OSMutexPend(queue->use_mutex, 0, &mutex_error);//互斥访问
 					memcpy(ret, queue->queue + queue->head * queue->unit, queue->unit);
					queue->length --;
					queue->head = (queue->head + 1) % queue->size;
					OSMutexPost (queue->use_mutex);
					return 1;
				}
			}
		}
	} 
	return 0; 	
 }

 /*
  *	入队
  * @param 队列结构
  * @param 出队成员
  * @return执行结果
  *			0：失败
  *			1：成功
  */
 unsigned char offer(calc_queue *queue, const void * source)
 {
 	INT8U mutex_error = 0;
 	if(queue){
		if(queue->queue){
			if(source){
 				if(queue->size >= queue->length + 1){
					OSMutexPend(queue->use_mutex, 0, &mutex_error);//互斥访问
					memcpy(queue->queue + ((queue->head + queue->length) % queue->size) * queue->unit, source, queue->unit);
					queue->length++;
					OSMutexPost (queue->use_mutex);
					return 1;
				}
			}
		}
	}
	return 0;	
 }

 /*
  *	获取队列长度
  * @param 队列结构
  * @return 队列长度
  */
 unsigned long queue_length(const calc_queue *const queue)
 {
 	if(queue){
		if(queue->queue){
			return queue->length;
		}
	}
 	return 0;
 }

 /*
  *	清空队列
  * @param 队列结构
  * @param 队列保存缓冲区
  *			NULL：不保存队列内容，直接清空队列
  * @param 缓冲区size
  			0:不保存队列内容，直接清空队列
  * @return 保存的队列内容的size
  */
 unsigned long queue_clean(calc_queue *queue, void * buffer, unsigned long size)
 {
 	const unsigned long length = queue->length * queue->unit < size ? queue->length * queue->unit : size;
	if(buffer){
		if(length){
		 	if(queue->head + queue->length < queue->size){
				memcpy(buffer, queue->queue + queue->head * queue->unit, length);
			}else{
				if(length < (queue->size - queue->head) * queue->unit){
					memcpy(buffer, queue->queue + queue->head * queue->unit, length);
				}else{
					memcpy(buffer, queue->queue + queue->head * queue->unit, (queue->size - queue->head) * queue->unit);
					memcpy((char*)buffer + (queue->size - queue->head) * queue->unit, queue->queue, (queue->length - (queue->size - queue->head)) * queue->unit);
				}
			}
		}
	}
 	if(queue){
		queue->length = 0;
		queue->head = 0;
		if(queue->queue)
			memset(queue->queue, 0, queue->size * queue->unit);
	}
	return length;
 }

