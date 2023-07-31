/*
 * uart_base.h
 */

 #ifndef __UART_BASE_H__
 #define __UART_BASE_H__
 
 	#include "bus_type.h"
 	
	/*
	 * 监听器集合
	 */
	struct uart_callback{
		
		/*
		 * 收到字节监听器
		 */
		set_char_message recv_char;

		/*
		 * 接收字节完成监听器
		 */
		do_sth transport_finish;
	};
	
	typedef const struct uart_callback * (*get_uart_callback_funp)();

	/*
	 * 设置回调函数接口
	 */ 
 	struct uart_listener_s{

			/*
			 * 设置收到字符的回调函数
			 */
			const set_callback_recv_char_p set_on_recv_char_listener;

			/*
			 * 设置传输完成的回调函数
			 */
			const set_callback_transport_finish_p set_on_transport_finish_listener;

			/*
			 * 设置获取监听器的方法
			 */
			const get_uart_callback_funp get_uart_callback;
	};

	/*
	 * 设置接口
	 */
	extern const struct uart_listener_s uart_listener;
 #endif
