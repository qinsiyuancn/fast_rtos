/*
 * i2c_bus.c
 * create by qinsiyuan
 * 			on 2016-11-7
 * 提供回调的封装
 * 只起到封装和代码复用的作用
 * 无架构意义
 */
 #include "i2c_bus.h"

 /*
  *	获取i2c的监听器
  * @param 总线管理器
  * @return i2c监听器集合
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
  *	获取地址
  * @param i2c总线管理器
  * @param 总线序号
  * @return 地址
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
  *	i2c发送字节回调函数
  * @param 总线管理器
  * @param 总线序号
  * @param 字节缓存地址
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
  *	i2c总线收到字节的回调函数
  * @param 总线管理器
  * @param 总线序号
  * @param 收到的字符
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
  *	数据传输完成
  * @param 总线管理器
  * @param 总线序号
  */
 void i2c_base_transport_finish(const struct i2c_manager_s * i2c_manager, unsigned char fd)
 {
	const struct i2c_callback * callback = i2c_base_get_listener_callback(i2c_manager);
	if(callback)
		if(callback->finish_transport)
			callback->finish_transport(fd); 
 }

 /*
  *	获取需要处理的字节数
  * @param 总线管理器
  * @param 总线序号
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

