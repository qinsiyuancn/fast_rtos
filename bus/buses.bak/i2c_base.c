/*
 * i2c_base.c
 * create by qinsiyuan
 *			on 2016-11-7
 * i2c具体总线层中硬件无关部分
 * 负责与抽象层交互
 * 大部分作用是设置监听器(回调函数)
 */

 #include "i2c_base.h"

 /*
  *	监听器
  */
static struct i2c_callback listener = {NULL};

 /*
  *	设置收到字节监听器
  * @param 收到字节的回调函数
  */ 
static void set_callback_recv_char(set_char_message p)
{
	listener.recv_char = p;
}

 /*
  *	设置发送字节的监听器
  * @param 发送字符的监听器
  */
static void set_callback_send_char(get_char_message p)
{
	listener.send_char = p;										
}

 /*
  *	设置传输完成的监听器
  * @param 传输完成监听器
  */
static void set_transport_finish(do_sth p)
{										   
	listener.finish_transport = p;
}
 
 /*
  *	设置获取从地址的监听器
  * @param 获取从地址监听器
  */
static void set_callback_get_addr(get_uchar_message p)
{
	listener.get_addr = p;
}
 /*
  *	设置获取处理字节数的回调函数
  * @param 监听器
  */
static void set_callback_get_size(get_uchar_message p)
{
	listener.get_size = p;
}
 /*
  *	获取监听器
  *	@return 监听器
  */
static const struct i2c_callback * get_i2c_callback()
{
	return &listener;
}

/*
 * 对外接口
 */
const struct i2c_listener_s i2c_listener = {
											set_callback_get_addr,
											set_callback_recv_char, 
											set_callback_send_char,
											set_transport_finish,
											set_callback_get_size,											
											get_i2c_callback
											};
