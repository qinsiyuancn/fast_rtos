/*
 * i2c_base.c
 * create by qinsiyuan
 *			on 2016-11-7
 * i2c�������߲���Ӳ���޹ز���
 * ���������㽻��
 * �󲿷����������ü�����(�ص�����)
 */

 #include "i2c_base.h"

 /*
  *	������
  */
static struct i2c_callback listener = {NULL};

 /*
  *	�����յ��ֽڼ�����
  * @param �յ��ֽڵĻص�����
  */ 
static void set_callback_recv_char(set_char_message p)
{
	listener.recv_char = p;
}

 /*
  *	���÷����ֽڵļ�����
  * @param �����ַ��ļ�����
  */
static void set_callback_send_char(get_char_message p)
{
	listener.send_char = p;										
}

 /*
  *	���ô�����ɵļ�����
  * @param ������ɼ�����
  */
static void set_transport_finish(do_sth p)
{										   
	listener.finish_transport = p;
}
 
 /*
  *	���û�ȡ�ӵ�ַ�ļ�����
  * @param ��ȡ�ӵ�ַ������
  */
static void set_callback_get_addr(get_uchar_message p)
{
	listener.get_addr = p;
}
 /*
  *	���û�ȡ�����ֽ����Ļص�����
  * @param ������
  */
static void set_callback_get_size(get_uchar_message p)
{
	listener.get_size = p;
}
 /*
  *	��ȡ������
  *	@return ������
  */
static const struct i2c_callback * get_i2c_callback()
{
	return &listener;
}

/*
 * ����ӿ�
 */
const struct i2c_listener_s i2c_listener = {
											set_callback_get_addr,
											set_callback_recv_char, 
											set_callback_send_char,
											set_transport_finish,
											set_callback_get_size,											
											get_i2c_callback
											};
