/*
 * i2c_bus.h
 * created by qinsiyuan
 * 		on 2016-7-4
 * 总线与抽象层交互接口
 */

 #ifndef __I2C_BUS_H__
 #define __I2C_BUS_H__

 #include "i2c_base.h"
 
 /*
  *	i2c总线的两种模式
  */
 enum i2c_mode{
	slave,
	master
 };

 /*
  *	总线管理器
  * 向上层提供硬件相关操作接口
  */
 struct i2c_manager_s{
 	
	/*
	 * 总线总数
	 */
	const unsigned char count;

	/*
	 * 总线初始化函数
	 */
	int (*bus_init)(unsigned char fd, enum i2c_mode mode);

	/*
	 * 总线开始工作
	 */
	unsigned char (*work)( unsigned char fd );

	/*
	 * 停止总线工作
	 */
	unsigned int (*stop)( unsigned char fd );

	/*
	 * 中断处理函数
	 */
	void (*IRQHandler)(unsigned char fd);

	/*
	 * 监听器
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
 
