/*
 * uart_bus.c
 */


 #include "uart_bus.h"
 const struct uart_callback * uart_base_get_listener_callback(const struct uart_manager_s * uart_manager)
 {
 	if(uart_manager){
		if(uart_manager->listener){
			if(uart_manager->listener){
				if(uart_manager->listener->get_uart_callback)
					return uart_manager->listener->get_uart_callback();
			}
		}	
	}
 	return NULL;
 }

 unsigned char uart_base_recv_char(const struct uart_manager_s * uart_manager,unsigned char fd, char c)
 {
	const struct uart_callback * callback = uart_base_get_listener_callback(uart_manager);
	if(callback)
		if(callback->recv_char)
			return callback->recv_char(fd, c);
	return 0;	 
 }

 void uart_base_transport_finish(const struct uart_manager_s * uart_manager, unsigned char fd)
 {
	const struct uart_callback * callback = uart_base_get_listener_callback(uart_manager);
	if(callback)
		if(callback->transport_finish)
			callback->transport_finish(fd); 
 }
 
