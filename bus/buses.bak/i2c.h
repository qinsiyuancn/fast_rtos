/*
 * i2c.h
 * create by qinsiyuan
 * 			on 2016-7-26
 */

 #ifndef __I2C_H__
 #define __I2C_H__

	#include "i2c_lpc17xx.h"


	#define RW_BIT			0x01

	#define RD_BIT RW_BIT
	#define WR_BIT ~RW_BIT

	#define set_rdbit(addr) addr |= RD_BIT
	#define set_wrbit(addr)	addr &= WR_BIT

	/*
	 * i2c�豸�������õĽṹ��
	 * ����ṹ�����������ļ���Ľṹ���������߲��
	 */
	struct i2c_device{const unsigned char fd; const unsigned char slave_addr;};

	/*
	 * I2C�Ự
	 * �����������ݴ�������ݿ���
	 * ÿ���Ự��Ӧһ��I2C�������߷�Ӳ������
	 */
	struct i2c_session{
		struct{
			unsigned long size;//��󳤶�
			unsigned long proress;//��ǰ����
			unsigned char addr_rw;//�Ե�ַ����ģʽʱ��ʾ�Է���ַ����ģʽʱ��ʾ�Լ��ĵ�ַ
			union {
				char * input;//��ȡ��Ϣ������
				const char * output;
			}buffer_io;
		}msg;//������������
		struct{
			//unsigned char sem;
			OS_EVENT  * sem;//��������(ͬ��)
//			OS_EVENT  * mutex;//���ڶ�ռ(����)
		}ctrler;//��������
	};

	/*
	 * ���ôӵ�ַ
	 * ��ģʽ����Զ˵Ĵӵ�ַ
	 * ��ģʽ��ʾ�����Լ��Ĵӵ�ַ
	 * @param �������
	 * @param �ӵ�ַ
	 */
	void i2c_slave_address(unsigned char fd, unsigned char addr_rw);

	/*
	 * i2c��ȡ
	 * @param �������
	 * @param ���ݻ���
	 * @param �������ռ�
	 * @return ʵ��д�����ߵ��ֽ���
	 */
	unsigned long i2c_read(unsigned char fd, char * buffer, unsigned long size);

	/*
	 * i2cд
	 * @param �������
	 * @param д�����ߵĻ���
	 * @param д�����ߵ��ֽ���
	 * @return ʵ��д�����ߵ��ֽ���
	 */
	unsigned long i2c_write(unsigned char fd, const char * buffer, unsigned long size);
	
	/*
	 * ��ʼ��i2c����Ӳ����ز�������
	 * @param �������
	 * @param ����ģʽ
	 * @return
	 */
	unsigned char i2c_bus_init(unsigned char fd, enum i2c_mode mode);

	/*
	 * i2c��ʼ��
	 * @param �������
	 * @param ����ģʽ
	 * @return
	 */
	unsigned char i2c_init(unsigned char fd, enum i2c_mode mode);

	/*
	 * ��ģʽ��ʼ��
	 * @param �������
	 * @param �Լ��Ĵӵ�ַ
	 * @return 
	 */
	unsigned char i2c_init_slave(unsigned char fd, unsigned char addr);
	
	/*
	 * ��ģʽ��ʼ��
	 * @param �������
	 * @return 
	 */
	unsigned char i2c_init_master(unsigned char fd);
 #endif
