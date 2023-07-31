/*
 * i2c_bus.c
 * create by qinsiyuan
 * 			on 2016-11-7
 * �ṩ�ص��ķ�װ
 * ֻ�𵽷�װ�ʹ��븴�õ�����
 * �޼ܹ�����
 */
 #include "i2c_bus.h"

 /*
  *	��ȡi2c�ļ�����
  * @param ���߹�����
  * @return i2c����������
  */
 const struct i2c_callback * i2c_base_get_listener_callback(const struct i2c_manager_s * i2c_manager)
 {
 	if(i2c_manager){
		if(i2c_manager->listener){
			if(i2c_manager->listener){
				if(i2c_manager->listener->get_i2c_callback)
					return i2c_manager->listener->get_i2c_callback();
			}
		}	
	}
 	return NULL;
 }

 /*
  *	��ȡ��ַ
  * @param i2c���߹�����
  * @param �������
  * @return ��ַ
  */
 unsigned char i2c_base_get_addr(const struct i2c_manager_s * i2c_manager, unsigned char fd)
 {
 	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->get_addr)
			return callback->get_addr(fd);
	return 0;
 }

 /*
  *	i2c�����ֽڻص�����
  * @param ���߹�����
  * @param �������
  * @param �ֽڻ����ַ
  * @return
  */
 char i2c_base_send_char(const struct i2c_manager_s * i2c_manager, unsigned char fd, char * c)
 {
	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->send_char)
			return callback->send_char(fd, c);
	return 0; 
 }

 /*
  *	i2c�����յ��ֽڵĻص�����
  * @param ���߹�����
  * @param �������
  * @param �յ����ַ�
  * @return 
  */
 unsigned char i2c_base_recv_char(const struct i2c_manager_s * i2c_manager,unsigned char fd, char c)
 {
	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->recv_char)
			return callback->recv_char(fd, c);
	return 0;	 
 }

 /*
  *	���ݴ������
  * @param ���߹�����
  * @param �������
  */
 void i2c_base_transport_finish(const struct i2c_manager_s * i2c_manager, unsigned char fd)
 {
	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->finish_transport)
			callback->finish_transport(fd); 
 }

 /*
  *	��ȡ��Ҫ������ֽ���
  * @param ���߹�����
  * @param �������
  * @return
  */
 unsigned char i2c_base_get_msg_size(const struct i2c_manager_s * i2c_manager, unsigned char fd)
 {
	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->get_size)
			return callback->get_size(fd);
	return 0; 
 }

