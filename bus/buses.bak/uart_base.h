/*
 * uart_base.h
 */

 #ifndef __UART_BASE_H__
 #define __UART_BASE_H__
 
 	#include "bus_type.h"
 	
	/*
	 * ����������
	 */
	struct uart_callback{
		
		/*
		 * �յ��ֽڼ�����
		 */
		set_char_message recv_char;

		/*
		 * �����ֽ���ɼ�����
		 */
		do_sth transport_finish;
	};
	
	typedef const struct uart_callback * (*get_uart_callback_funp)();

	/*
	 * ���ûص������ӿ�
	 */ 
 	struct uart_listener_s{

			/*
			 * �����յ��ַ��Ļص�����
			 */
			const set_callback_recv_char_p set_on_recv_char_listener;

			/*
			 * ���ô�����ɵĻص�����
			 */
			const set_callback_transport_finish_p set_on_transport_finish_listener;

			/*
			 * ���û�ȡ�������ķ���
			 */
			const get_uart_callback_funp get_uart_callback;
	};

	/*
	 * ���ýӿ�
	 */
	extern const struct uart_listener_s uart_listener;
 #endif
