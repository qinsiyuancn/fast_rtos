/*
 * i2c.c
 * created by qinsiyuan
 * 		on 2016-6-29
 * I2C����
 * �ṩ��Ӳ���޹ص��߼�
 */
#include "i2c.h"

/*
 * i2c��д���ƽṹ
 */
static struct i2c_session *sessons = NULL;

/*
 * ��ȡ�ӻ���ַ�Ļص�����
 * @param i2c��������
 * @return i2c�ӵ�ַ�Ͷ�дλ
 */
static unsigned char on_i2c_get_addr(unsigned char fd)
{
	return sessons[fd].msg.addr_rw;
}

/*
 * �յ��ֽڵĻص�����
 * @param i2c��������
 * @param ���յ��ֽ�
 * @return �������������ܹ����յ��ַ�������
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
 * ���ͻ����е��ַ��ص�����
 * @param �������
 * @param �����ַ�ָ��
 * @return �Ƿ��ȡ�������е�����
 *			0����ȡ�ɹ�
 *			1����ȡʧ��			
 */
static char on_i2c_send_char(unsigned char fd, char * c)
{
	if(c){
		if(sessons){
			if(sessons[fd].msg.buffer_io.output){
				if(sessons[fd].msg.size > sessons[fd].msg.proress){//���ͽ�����־	
					*c = sessons[fd].msg.buffer_io.output[sessons[fd].msg.proress++];
					return 0;
				}
			}
		}
	}
	return 1;		
}

/*
 * ���ͻ����е��ֽ���
 * @param �������
 * @return ���������ݳ���
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
 * ������ϵĻص�����
 * @param �������
 */
static void on_transport_finish(unsigned char fd)
{
//	i2c_bus_manager->stop(fd);	
//	sessons[fd].ctrler.sem = 1 ;
	OSSemPost( sessons[fd].ctrler.sem );
}

/*
 * ���ûص�����
 * @param �����������
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
 * ���ݴ���
 * @param �������
 * @param ���ߴ��䳤��
 */
static unsigned long i2c_transport(unsigned char fd, unsigned long size)
{
//	INT8U mutex_error = 0;
	INT8U sem_error = 0;

	if(size){
		if(fd < i2c_bus_manager->count){
//			if(sessons[fd].ctrler.sem){
//				OSMutexPend(sessons[fd].ctrler.mutex, 0, &mutex_error);//�������
				sessons[fd].msg.size = size;
				sessons[fd].msg.proress = 0;
				i2c_bus_manager->work(fd);
				OSSemPend(sessons[fd].ctrler.sem, 0, &sem_error);//�ȴ��������
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
 * ���ôӵ�ַ
 * ��ģʽ����Զ˵Ĵӵ�ַ
 * ��ģʽ��ʾ�����Լ��Ĵӵ�ַ
 * @param �������
 * @param �ӵ�ַ
 */
void i2c_slave_address(unsigned char fd, unsigned char addr_rw)
{
//	INT8U mutex_error = 0;
//	OSMutexPend(sessons[fd].ctrler.mutex, 0, &mutex_error);//�������
	sessons[fd].msg.addr_rw = addr_rw << 1;
//	OSMutexPost (sessons[fd].ctrler.mutex);
}

/*
 * i2c��ȡ
 * @param �������
 * @param ���ݻ���
 * @param �������ռ�
 * @return ʵ��д�����ߵ��ֽ���
 */
unsigned long i2c_read(unsigned char fd, char * buffer, unsigned long size)
{
	set_rdbit(sessons[fd].msg.addr_rw);
	sessons[fd].msg.buffer_io.input = buffer;
	return i2c_transport(fd, size);
}

/*
 * i2cд
 * @param �������
 * @param д�����ߵĻ���
 * @param д�����ߵ��ֽ���
 * @return ʵ��д�����ߵ��ֽ���
 */
unsigned long i2c_write(unsigned char fd, const char * buffer, unsigned long size)
{
	set_wrbit(sessons[fd].msg.addr_rw);
	sessons[fd].msg.buffer_io.output = buffer;
	return i2c_transport(fd, size);
}

/*
 * ��ʼ��i2c����Ӳ����ز�������
 * @param �������
 * @param ����ģʽ
 * @return
 */
unsigned char i2c_bus_init(unsigned char fd, enum i2c_mode mode)
{
	return i2c_bus_manager->bus_init(fd, mode);
}

/*
 * i2c��ʼ��
 * @param �������
 * @param ����ģʽ
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
 * ��ģʽ��ʼ��
 * @param �������
 * @param �Լ��Ĵӵ�ַ
 * @return 
 */
unsigned char i2c_init_slave(unsigned char fd, unsigned char addr)
{  	
	i2c_slave_address(fd, addr);
	return i2c_init(fd, slave);
}

/*
 * ��ģʽ��ʼ��
 * @param �������
 * @return 
 */
unsigned char i2c_init_master(unsigned char fd)
{
	return i2c_init(fd, master);
}
