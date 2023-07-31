/*
 * i2c_bus.h
 * created by qinsiyuan
 * 		on 2016-7-4
 * ���������㽻���ӿ�
 */

 #ifndef __I2C_BUS_H__
 #define __I2C_BUS_H__

 #include "i2c_base.h"
 
 /*
  *	i2c���ߵ�����ģʽ
  */
 enum i2c_mode{
	slave,
	master
 };

 /*
  *	���߹�����
  * ���ϲ��ṩӲ����ز����ӿ�
  */
 struct i2c_manager_s{
 	
	/*
	 * ��������
	 */
	const unsigned char count;

	/*
	 * ���߳�ʼ������
	 */
	int (*bus_init)(unsigned char fd, enum i2c_mode mode);

	/*
	 * ���߿�ʼ����
	 */
	unsigned char (*work)( unsigned char fd );

	/*
	 * ֹͣ���߹���
	 */
	unsigned int (*stop)( unsigned char fd );

	/*
	 * �жϴ�����
	 */
	void (*IRQHandler)(unsigned char fd);

	/*
	 * ������
	 */
	const struct i2c_listener_s * listener ;
 };
 

 extern const struct i2c_callback * i2c_base_get_listener_callback(const struct i2c_manager_s *);
 extern unsigned char i2c_base_get_addr(const struct i2c_manager_s * , unsigned char );
 extern char i2c_base_send_char(const struct i2c_manager_s * , unsigned char , char *);
 extern unsigned char i2c_base_recv_char(const struct i2c_manager_s * ,unsigned char , char );
 extern void i2c_base_transport_finish(const struct i2c_manager_s * , unsigned char );
 extern unsigned char i2c_base_get_msg_size(const struct i2c_manager_s * i2c_manager, unsigned char fd); 
 #endif
 
