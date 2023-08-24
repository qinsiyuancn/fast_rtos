/*
 * i2c.c
 * created by qinsiyuan
 * 		on 2016-6-29
 * I2C驱动
 * 提供与硬件无关的逻辑
 */
#include "i2c.h"

/*
 * i2c读写控制结构
 */
static struct i2c_session *sessons = NULL;

/*
 * 获取从机地址的回调函数
 * @param i2c总线索引
 * @return i2c从地址和读写位
 */
static unsigned char on_i2c_get_addr(unsigned char fd)
{
	return sessons[fd].msg.addr_rw;
}

/*
 * 收到字节的回调函数
 * @param i2c总线索引
 * @param 接收的字节
 * @return 接收能力，即能够接收的字符个数。
 */
static unsigned char on_i2c_recv_char(unsigned char fd, char c)
{
	if(sessons){
		if(sessons[fd].msg.buffer_io.input){
			if(sessons[fd].msg.size > sessons[fd].msg.proress){
				sessons[fd].msg.buffer_io.input[sessons[fd].msg.proress++] = c;
				return sessons[fd].msg.size - sessons[fd].msg.proress;
			}
		}
	}
	return 0;
}

/*
 * 发送缓存中的字符回调函数
 * @param 总线序号
 * @param 接收字符指针
 * @return 是否获取到缓存中的数据
 *			0：获取成功
 *			1：获取失败			
 */
static char on_i2c_send_char(unsigned char fd, char * c)
{
	if(c){
		if(sessons){
			if(sessons[fd].msg.buffer_io.output){
				if(sessons[fd].msg.size > sessons[fd].msg.proress){//发送结束标志	
					*c = sessons[fd].msg.buffer_io.output[sessons[fd].msg.proress++];
					return 0;
				}
			}
		}
	}
	return 1;		
}

/*
 * 发送缓存中的字节数
 * @param 总线序号
 * @return 待处理数据长度
 */
static unsigned char on_get_msg_size(unsigned char fd)
{
	if(sessons){
		if(sessons[fd].msg.buffer_io.output){
			return sessons[fd].msg.size;
		}
	}
	return 0;
}

/*
 * 传输完毕的回调函数
 * @param 总线序号
 */
static void on_transport_finish(unsigned char fd)
{
//	i2c_bus_manager->stop(fd);	
//	sessons[fd].ctrler.sem = 1 ;
	OSSemPost( sessons[fd].ctrler.sem );
}

/*
 * 设置回调函数
 * @param 设置总线序号
 */
static void set_callback(unsigned char fd)
{
	 i2c_bus_manager->listener->set_on_addr_listener(on_i2c_get_addr);
	 i2c_bus_manager->listener->set_on_recv_char_listener(on_i2c_recv_char);
	 i2c_bus_manager->listener->set_on_send_char_listener(on_i2c_send_char);
	 i2c_bus_manager->listener->set_on_transport_finish_listener(on_transport_finish);
	 i2c_bus_manager->listener->set_on_get_size_listener(on_get_msg_size);
}

/*
 * 数据传输
 * @param 总线序号
 * @param 总线传输长度
 */
static unsigned long i2c_transport(unsigned char fd, unsigned long size)
{
//	INT8U mutex_error = 0;
	INT8U sem_error = 0;

	if(size){
		if(fd < i2c_bus_manager->count){
//			if(sessons[fd].ctrler.sem){
//				OSMutexPend(sessons[fd].ctrler.mutex, 0, &mutex_error);//互斥访问
				sessons[fd].msg.size = size;
				sessons[fd].msg.proress = 0;
				i2c_bus_manager->work(fd);
				OSSemPend(sessons[fd].ctrler.sem, 0, &sem_error);//等待传输完毕
				sessons[fd].msg.size = 0;
				sessons[fd].msg.buffer_io.input = NULL;
				sessons[fd].msg.buffer_io.output = NULL;
//				OSMutexPost (sessons[fd].ctrler.mutex);
				return sessons[fd].msg.proress;
//			}
		}
	}
	return 0;
}

/*
 * 设置从地址
 * 主模式代表对端的从地址
 * 从模式表示设置自己的从地址
 * @param 总线序号
 * @param 从地址
 */
void i2c_slave_address(unsigned char fd, unsigned char addr_rw)
{
//	INT8U mutex_error = 0;
//	OSMutexPend(sessons[fd].ctrler.mutex, 0, &mutex_error);//互斥访问
	sessons[fd].msg.addr_rw = addr_rw << 1;
//	OSMutexPost (sessons[fd].ctrler.mutex);
}

/*
 * i2c读取
 * @param 总线序号
 * @param 数据缓存
 * @param 缓存最大空间
 * @return 实际写入总线的字节数
 */
unsigned long i2c_read(unsigned char fd, char * buffer, unsigned long size)
{
	set_rdbit(sessons[fd].msg.addr_rw);
	sessons[fd].msg.buffer_io.input = buffer;
	return i2c_transport(fd, size);
}

/*
 * i2c写
 * @param 总线序号
 * @param 写入总线的缓存
 * @param 写入总线的字节数
 * @return 实际写入总线的字节数
 */
unsigned long i2c_write(unsigned char fd, const char * buffer, unsigned long size)
{
	set_wrbit(sessons[fd].msg.addr_rw);
	sessons[fd].msg.buffer_io.output = buffer;
	return i2c_transport(fd, size);
}

/*
 * 初始化i2c总线硬件相关部分驱动
 * @param 总线序号
 * @param 主从模式
 * @return
 */
unsigned char i2c_bus_init(unsigned char fd, enum i2c_mode mode)
{
	return i2c_bus_manager->bus_init(fd, mode);
}

/*
 * i2c初始化
 * @param 总线序号
 * @param 主从模式
 * @return
 */
unsigned char i2c_init(unsigned char fd, enum i2c_mode mode)
{
//	INT8U perr[1] = {0};
	set_callback(fd);
	if(!sessons){
		sessons = malloc(sizeof(struct i2c_session) * i2c_bus_manager->count);
		if(sessons)
			memset (sessons, 0, sizeof(struct i2c_session) * i2c_bus_manager->count);
		else
			return 0;
	}
	if(i2c_bus_manager->count > fd)
	{
		if(!sessons[fd].ctrler.sem)
			sessons[fd].ctrler.sem = OSSemCreate(0);
//		if(!sessons[fd].ctrler.mutex)
//			sessons[fd].ctrler.mutex = OSMutexCreate(2, perr);
		if(sessons[fd].ctrler.sem/* && sessons[fd].ctrler.mutex*/)
			i2c_bus_init(fd, mode);
//		else return 0;
	}
	return 1;
}

/*
 * 从模式初始化
 * @param 总线序号
 * @param 自己的从地址
 * @return 
 */
unsigned char i2c_init_slave(unsigned char fd, unsigned char addr)
{  	
	i2c_slave_address(fd, addr);
	return i2c_init(fd, slave);
}

/*
 * 主模式初始化
 * @param 总线序号
 * @return 
 */
unsigned char i2c_init_master(unsigned char fd)
{
	return i2c_init(fd, master);
}
