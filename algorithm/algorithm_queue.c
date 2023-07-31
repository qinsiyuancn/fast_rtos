/*
 * algorithm_queue.c
 * create by qinsiyuan
 *			on 2016-7-13
 * ���нṹ��װ
 */
 #include "algorithm_queue.h"

 /*
  *	��������
  * @param ��λ�ռ�
  * @param ���г�Ա����
  * @return ���нṹ
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
  *	ɾ������
  * @param ���нṹ
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
  *	����
  * @param ���нṹ
  * @param ���ӳ�Ա
  * @return ִ�н��
  *			0��ʧ��
  *			1���ɹ�
  */
 unsigned char poll(calc_queue *queue, void * ret)
 {
 	INT8U mutex_error = 0;
 	if(queue){
		if(queue->queue){
			if(queue->length){
				if(ret){
					OSMutexPend(queue->use_mutex, 0, &mutex_error);//�������
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
  *	���
  * @param ���нṹ
  * @param ���ӳ�Ա
  * @returnִ�н��
  *			0��ʧ��
  *			1���ɹ�
  */
 unsigned char offer(calc_queue *queue, const void * source)
 {
 	INT8U mutex_error = 0;
 	if(queue){
		if(queue->queue){
			if(source){
 				if(queue->size >= queue->length + 1){
					OSMutexPend(queue->use_mutex, 0, &mutex_error);//�������
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
  *	��ȡ���г���
  * @param ���нṹ
  * @return ���г���
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
  *	��ն���
  * @param ���нṹ
  * @param ���б��滺����
  *			NULL��������������ݣ�ֱ����ն���
  * @param ������size
  			0:������������ݣ�ֱ����ն���
  * @return ����Ķ������ݵ�size
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

