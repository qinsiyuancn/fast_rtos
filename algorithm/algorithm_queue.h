/*
 * algorithm_queue.h
 * create by qinsiyuan
 *			on 2016-7-26
 * ���нṹ��װ
 */

 #ifndef __ALGORITHM_QUEUE_H__
 #define __ALGORITHM_QUEUE_H__

	#include "ucos_ii.h"
	#include <string.h>
	#include <stdlib.h>

 /*
  *	���нṹ
  */
 typedef struct{
 	
	/*
	 * ���г�Ա��
	 */
 	unsigned long size;
	
	/*
	 * ������Առ�õĿռ�
	 */
	unsigned long unit;

	/*
	 * ����洢��ָ��
	 */
 	char * queue;

	/*
	 * ����ͷ����
	 */
	unsigned long head;

	/*
	 * ����ͷ����
	 */
	unsigned long length;

	/*
	 * ������ʿ���
	 */
	OS_EVENT  * use_mutex;
 } calc_queue;
  
 /*
  *	��������
  * @param ��λ�ռ�
  * @param ���г�Ա����
  * @return ���нṹ
  */
  calc_queue * queue_create(unsigned long , unsigned long );

 /*
  *	ɾ������
  * @param ���нṹ
  */
  void queue_delete(calc_queue *);
  
 /*
  *	����
  * @param ���нṹ
  * @param ���ӳ�Ա
  * @return ִ�н��
  *			0��ʧ��
  *			1���ɹ�
  */
  unsigned char poll(calc_queue *, void * );

 /*
  *	���
  * @param
  * @param
  * @return 
  */
  unsigned char offer(calc_queue *, const void * );

 /*
  *	��ȡ���г���
  * @param ���нṹ
  * @return ���г���
  */
  unsigned long queue_length(const calc_queue * const );

 /*
  *	��ն���
  * @param ���нṹ
  * @param ���б��滺����
  *			NULL��������������ݣ�ֱ����ն���
  * @param ������size
  *			0:������������ݣ�ֱ����ն���
  * @return ����Ķ������ݵ�size
  */
  unsigned long queue_clean(calc_queue *queue, void * , unsigned long );

 #endif
