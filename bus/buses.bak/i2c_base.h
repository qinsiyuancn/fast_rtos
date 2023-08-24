/*
 * i2c_base.h
 */

#ifndef __I2C_BASE_H__
#define __I2C_BASE_H__
	#include "bus_type.h"
	
	/*
	 * 总线回调函数集合
	 */
	struct i2c_callback{
		set_char_message recv_char;
		get_char_message send_char;
		do_sth finish_transport;
		get_uchar_message get_addr;
		get_uchar_message get_size;
	};

	typedef const struct i2c_callback *	(*funp_get_i2c_callback)();
	
	/*
	 * 监听器类型
	 */
	struct i2c_listener_s{
			const set_callback_get_uchar set_on_addr_listener;
			const set_callback_recv_char_p set_on_recv_char_listener;
			const set_callback_send_char_p set_on_send_char_listener;
			const set_callback_transport_finish_p set_on_transport_finish_listener;
			const set_callback_get_uchar set_on_get_size_listener;
			const funp_get_i2c_callback get_i2c_callback;
	};

	/*
	 * 监听器
	 */
	extern const struct i2c_listener_s i2c_listener;

#endif
