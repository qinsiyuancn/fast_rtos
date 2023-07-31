/*
 * uart_base.c
 * ������������
 * ��Ҫ����ص�����
 */

 #include "uart_base.h"

 /*
  *	����������
  */
 static struct uart_callback listener = { NULL };

 /*
  *	�����յ��ַ��ļ�����
  * @param �յ��ֽڵĺ���ָ��
  */
 static void set_callback_recv_char(set_char_message p)
 {
	listener.recv_char = p;
 }

 /*
  *	���ô�����ɵļ�����
  * @param ������ɻص�����ָ��
  */
 static void set_transport_finish(do_sth p)
 {										   
	listener.transport_finish = p;
 }

 /*
  *	��ȡ����������
  * @param ��ȡ������
  */
 static const struct uart_callback * get_uart_callback()
 {
	return &listener;
 }

 /*
  *	����ӿ�
  */
 const struct uart_listener_s uart_listener = {
 											set_callback_recv_char, 
											set_transport_finish,
											get_uart_callback
											};
