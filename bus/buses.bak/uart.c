/*
 * uart.c
 * create by qinsiyuan
 *		create on 2016-7-5
 * 
 */
 #include "uart.h"

 /*
  *	总线传输控制结构
  */
 static struct uart_sessor_s{
 	
	/*
	 * 读取uart总线的缓冲区
	 */
	calc_queue * aio;
	OS_EVENT  * use_mutex;//用于独占(互斥)
	struct{
		OS_EVENT  * sem;//用于阻塞(同步)
//		OS_EVENT  * mutex;//用于独占(互斥)
	}read_ctrler;//控制描述
	struct{
		OS_EVENT  * sem;//用于阻塞(同步)
//		OS_EVENT  * mutex;//用于独占(互斥)
	}write_ctrler;//控制描述
 } * uart_sesson = NULL;

/*
 * 收到字符的回调函数
 * @param 总线序列
 * @param 接收到的字符
 * @return 接受能力
 * 返回1表示不再接收
 * 返回0表示有能力继续接收
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
 * 传输完毕的回调函数(串口只有发送完会调用)
 * @param 总线序号
 */
static void on_transport_finish(unsigned char fd)
{
	if(uart_sesson[fd].write_ctrler.sem)
		OSSemPost( uart_sesson[fd].write_ctrler.sem );
}

/*
 * 设置回调函数
 */
static void set_callback()
{
	uart_bus_manager_pointer->listener->set_on_transport_finish_listener(on_transport_finish);
	uart_bus_manager_pointer->listener->set_on_recv_char_listener(on_recv_char); 	
}

/*
 * 初始化准备使用的串口，并设置独占
 * @param 总线序号
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
		OSMutexPend(uart_sesson[fd].use_mutex, 0, &mutex_error);//互斥访问
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
  *	写串口
  * @param 总线序号
  * @param 写入数据缓存
  * @param 写入总线的长度
  * @return 实际写入总线的长度
  */
 unsigned long uart_write(unsigned char fd, const char * buffer, unsigned long size)
 {
 	unsigned long progress = 0;
//	INT8U mutex_error = 0;
	INT8U sem_error = 0;
	if(!size)return 0;
	if(!buffer)return 0;
//	OSMutexPend(uart_sesson[fd].write_ctrler.mutex, 0, &mutex_error);//互斥访问
	for(progress = 0; progress < size; progress++){
		uart_bus_manager_pointer->send(fd, buffer[progress]);
		OSSemPend(uart_sesson[fd].write_ctrler.sem, 0, &sem_error);//等待传输完毕
	}
//	OSMutexPost (uart_sesson[fd].write_ctrler.mutex);
 	return progress;
 }

 /*
  *	读取总线上的一个字节
  * @param 总线序号
  * @return	从总线上获取到的字符
  */
 static char uart_getch(unsigned char fd)
 {
 	char ret[1] = {0};
	INT8U sem_error = 0;
	if(uart_sesson[fd].aio){
		do{
			if(!queue_length(uart_sesson[fd].aio))
				OSSemPend(uart_sesson[fd].read_ctrler.sem, 0, &sem_error);//等待传输完毕
  		}while(!poll(uart_sesson[fd].aio, ret));//如果出队列失败，重新出队
	}
	return *ret;
 }

 /*
  *	从总线中获取一个字符
  * @param 总线序号
  * @return 字符
  */
 char uart_getchar(unsigned char fd)
 {
 	char ret = 0;
// 	INT8U mutex_error = 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//互斥访问
	ret = uart_getch(fd);
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return ret;	
 }

 /*
  * 从总线上读取指定长度的数据
  *	@param 总线序号
  * @param 缓存
  * @param 读取的长度
  * @return 实际读取的长度
  */
 unsigned long uart_read(unsigned char fd, char * buffer, unsigned long size)
 {
 	unsigned long i = 0;
//	INT8U mutex_error = 0;
	if(!size)return 0;
	if(!buffer)return 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//互斥访问
	for(i = 0; i < size; i++){
		buffer[i] = uart_getch(fd);
	}
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return i;
 }

 /*
  *	情况串口缓冲区
  * @param 总线序号
  * @param 将总线队列上的数据复制到的缓存，如果为NULL，只执行清空命令
  * @param 缓存size，如果为0，只执行情况命令
  * @return
  */
 unsigned long uart_read_clean(unsigned char fd, char * buffer, unsigned long size)
 {
//	INT8U mutex_error = 0;
	unsigned long length = 0;
//	OSMutexPend(uart_sesson[fd].read_ctrler.mutex, 0, &mutex_error);//互斥访问
	length = queue_clean(uart_sesson[fd].aio, buffer, size);
//	OSMutexPost (uart_sesson[fd].read_ctrler.mutex);
	return length;
 }

 /*
  *	释放总线
  * @param 总线序号
  */
 void uart_release(unsigned char fd)
 {
 	queue_delete(uart_sesson[fd].aio);
	uart_sesson[fd].aio = NULL;
	OSMutexPost (uart_sesson[fd].use_mutex); 	
 }
 
 
