/*
 * uart_base.c
 * 串口驱动父类
 * 主要负责回调工作
 */

 #include "uart_base.h"

 /*
  *	监听器集合
  */
 static struct uart_callback listener = { NULL };

 /*
  *	设置收到字符的监听器
  * @param 收到字节的函数指针
  */
 static void set_callback_recv_char(set_char_message p)
 {
	listener.recv_char = p;
 }

 /*
  *	设置传输完成的监听器
  * @param 接收完成回调函数指针
  */
 static void set_transport_finish(do_sth p)
 {										   
	listener.transport_finish = p;
 }

 /*
  *	获取监听器集合
  * @param 获取监听器
  */
 static const struct uart_callback * get_uart_callback()
 {
	return &listener;
 }

 /*
  *	对外接口
  */
 const struct uart_listener_s uart_listener = {
 											set_callback_recv_char, 
											set_transport_finish,
											get_uart_callback
											};
