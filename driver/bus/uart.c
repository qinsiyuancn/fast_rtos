/*
 * uart.c
 * create by qinsiyuan
 *		create on 2016-7-5
 * 
 */
 #include "uart.h"

 /*
  *	���ߴ�����ƽṹ
  */
 static struct uart_sessor_s{
 	
	/*
	 * ��ȡuart���ߵĻ�����
	 */
	calc_queue * aio;
	OS_EVENT  * use_mutex;//���ڶ�ռ(����)
	struct{
		OS_EVENT  * sem;//��������(ͬ��)
//		OS_EVENT  * mutex;//���ڶ�ռ(����)
	}read_ctrler;//��������
	struct{
		OS_EVENT  * sem;//��������(ͬ��)
//		OS_EVENT  * mutex;//���ڶ�ռ(����)
	}write_ctrler;//��������
 } * uart_sesson = NULL;

/*
 * �յ��ַ��Ļص�����
 * @param ��������
 * @param ���յ����ַ�
 * @return ��������
 * ����1��ʾ���ٽ���
 * ����0��ʾ��������������
 */
static unsigned char on_recv_char(unsigned char fd, char c)
{
	if(uart_sesson[fd].aio){
		if(offer(uart_sesson[fd].aio, &c)){
			OSSemPost( uart_sesson[fd].read_ctrler.sem );
			return 0;
		}
	}
	return 1;
}

/*
 * ������ϵĻص�����(����ֻ�з���������)
 * @param �������
 */
static void on_transport_finish(unsigned char fd)
{
	if(uart_sesson[fd].write_ctrler.sem)
		OSSemPost( uart_sesson[fd].write_ctrler.sem );
}

/*
 * ���ûص�����
 */
static void set_callback()
{
	uart_bus_manager_pointer->listener->set_on_transport_finish_listener(on_transport_finish);
	uart_bus_manager_pointer->listener->set_on_recv_char_listener(on_recv_char); 	
}

/*
 * ��ʼ��׼��ʹ�õĴ��ڣ������ö�ռ
 * @param �������
 * @return 
 */ 
unsigned char uart_use(unsigned char fd)
{
	INT8U mutex_error = 0;
	if(!uart_sesson){
		uart_sesson = malloc (sizeof(struct uart_sessor_s) * uart_bus_manager_pointer->count);
		if(uart_sesson){
			memset (uart_sesson, 0, sizeof(struct uart_sessor_s) * uart_bus_manager_pointer->count);
		}else{
			return 0;
		} 
	} 
	if(uart_bus_manager_pointer->count > fd){
		if(!uart_sesson[fd].use_mutex)
			uart_sesson[fd].use_mutex = OSMutexCreate(0, &mutex_error);
		OSMutexPend(uart_sesson[fd].use_mutex, 0, &mutex_error);//�������
		set_callback();	
		if(!uart_sesson[fd].read_ctrler.sem)
			uart_sesson[fd].read_ctrler.sem = OSSemCreate(0);
		if(!uart_sesson[fd].write_ctrler.sem)
			uart_sesson[fd].write_ctrler.sem = OSSemCreate(0);
//		if(!uart_sesson[fd].read_ctrler.mutex)
//			uart_sesson[fd].read_ctrler.mutex = OSMutexCreate(1, &mutex_error);
//		if(!uart_sesson[fd].read_ctrler.mutex)
//			uart_sesson[fd].read_ctrler.mutex = OSMutexCreate(1, &mutex_error);
 		uart_sesson[fd].aio = queue_create(1, 0x40);
		if(uart_sesson[fd].aio){
			queue_clean(uart_sesson[fd].aio, NULL, 0);
			uart_bus_manager_pointer->bus_init(fd, 9600);
			return 1;
		}
	}
	return 0; 
}

 /*
  *	д����
  * @param �������
  * @param д�����ݻ���
  * @param д�����ߵĳ���
  * @return ʵ��д�����ߵĳ���
  */
 unsigned long uart_write(unsigned char fd, const char * buffer, unsigned long size)
 {
 	unsigned long progress = 0;
//	INT8U mutex_error = 0;
	INT8U sem_error = 0;
	if(!size)return 0;
	if(!buffer)return 0;
//	OSMutexPend(uart_sesson[fd].write_ctrler.mutex, 0, &mutex_error);//�������
	for(progress = 0; progress < size; progress++){
		uart_bus_manager_pointer->send(fd, buffer[progress]);
		OSSemPend(uart_sesson[fd].write_ctrler.sem, 0, &sem_error);//�ȴ��������
	}
//	OSMutexPost (uart_sesson[fd].write_ctrler.mutex);
 	return progress;
 }

 /*
  *	��ȡ�����ϵ�һ���ֽ�
  * @param �������
  * @return	�������ϻ�ȡ�����ַ�
  */
 static char uart_getch(unsigned char fd)
 {
 	char ret[1] = {0};
	INT8U sem_error = 0;
	if(uart_sesson[fd].aio){
		do{
			if(!queue_length(uart_sesson[fd].aio))
				OSSemPend(uart_sesson[fd].read_ctrler.sem, 0, &sem_error);//�ȴ��������
  		}while(!poll(uart_sesson[fd].aio, ret));//���������ʧ�ܣ����³���
	}
	return *ret;
 }

 /*
  *	�������л�ȡһ���ַ�
  * @param �������
  * @return �ַ�
  */
 char uart_getchar(unsigned char fd)
 {
 	char ret = 0;
// 	INT8U mutex_error = 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//�������
	ret = uart_getch(fd);
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return ret;	
 }

 /*
  * �������϶�ȡָ�����ȵ�����
  *	@param �������
  * @param ����
  * @param ��ȡ�ĳ���
  * @return ʵ�ʶ�ȡ�ĳ���
  */
 unsigned long uart_read(unsigned char fd, char * buffer, unsigned long size)
 {
 	unsigned long i = 0;
//	INT8U mutex_error = 0;
	if(!size)return 0;
	if(!buffer)return 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//�������
	for(i = 0; i < size; i++){
		buffer[i] = uart_getch(fd);
	}
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return i;
 }

 /*
  *	������ڻ�����
  * @param �������
  * @param �����߶����ϵ����ݸ��Ƶ��Ļ��棬���ΪNULL��ִֻ���������
  * @param ����size�����Ϊ0��ִֻ���������
  * @return
  */
 unsigned long uart_read_clean(unsigned char fd, char * buffer, unsigned long size)
 {
//	INT8U mutex_error = 0;
	unsigned long length = 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//�������
	length = queue_clean(uart_sesson[fd].aio, buffer, size);
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return length;
 }

 /*
  *	�ͷ�����
  * @param �������
  */
 void uart_release(unsigned char fd)
 {
 	queue_delete(uart_sesson[fd].aio);
	uart_sesson[fd].aio = NULL;
	OSMutexPost (uart_sesson[fd].use_mutex); 	
 }
 
 
