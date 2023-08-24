/*
 * uart_bus.h
 * create by qinsiyuan
 * 			on 2016-7-7
 * uart总线与抽象层驱动接口
 */

 #ifndef __UART_BUS_H__
 #define __UART_BUS_H__

 #include "uart_base.h"
 	struct uart_manager_s{
	 	const unsigned char count;
		/*
		 * param fd
		 * param 波特率
		 */
		int (*bus_init)(unsigned char, unsigned long);
		unsigned char (*send)( unsigned char fd, char c);
		void (*IRQHandler)(unsigned char fd);
		const struct uart_listener_s * const listener;
 	};

	extern const struct uart_callback * uart_base_get_listener_callback(const struct uart_manager_s * );
	extern unsigned char uart_base_recv_char(const struct uart_manager_s * ,unsigned char , char );
	extern void uart_base_transport_finish(const struct uart_manager_s * , unsigned char );

 #endif
