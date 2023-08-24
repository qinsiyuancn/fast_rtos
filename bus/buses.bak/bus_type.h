/*
 * bus_callback_type.h
 * created by qinsiyuan
 * 		on 2016-7-3
 * 总线callback类型
 */


 #ifndef __BUS_TYPE_H__
 #define __BUS_TYPE_H__
	
	 #include <string.h>
	 #include <stdlib.h>
	 #include <stdio.h>
	
	 #include "ucos_ii.h"
	
	 #define FALSE 0
	 #define TRUE  1
	
	 typedef unsigned char (*get_uchar_message)(unsigned char);
	 typedef unsigned char (*set_char_message)(unsigned char, char);
	 typedef char (*get_char_message)(unsigned char , char *);
	 typedef void (*do_sth)(unsigned char);
	
	 typedef int (*irq_funp)(unsigned char, unsigned char);
	
	 typedef void (*set_callback_recv_char_p)(set_char_message);
	 typedef void (*set_callback_send_char_p)(get_char_message);
	 typedef void (*set_callback_transport_finish_p)(do_sth);
	 typedef void (*set_callback_get_uchar)(get_uchar_message);
																								
 #endif
