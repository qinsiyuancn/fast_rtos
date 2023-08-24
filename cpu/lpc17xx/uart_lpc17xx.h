/*
 * uart_lpc17xx.h
 * create by qinsiyuan
 *			on 2016-7-7
 * 用于与cpu相关的串口驱动部分
 */

 #ifndef __UART_LPC17XX_H__
 #define __UART_LPC17XX_H__
 
 	#include "board_manager.h"
	#if CPU_lpc17xx
	 	#include "uart_bus.h"
	
		#define IER_RBR		0x01
		#define IER_THRE	0x02
		#define IER_RLS		0x04
		
		#define IIR_PEND	0x01
		#define IIR_RLS		0x03
		#define IIR_RDA		0x02
		#define IIR_CTI		0x06
		#define IIR_THRE	0x01
		
		#define LSR_RDR		0x01
		#define LSR_OE		0x02
		#define LSR_PE		0x04
		#define LSR_FE		0x08
		#define LSR_BI		0x10
		#define LSR_THRE	0x20
		#define LSR_TEMT	0x40
		#define LSR_RXFE	0x80
	
		#define UART_BUS_INIT {\
						 {(LPC_UART_TypeDef *)LPC_UART0, {&LPC_PINCON->PINSEL0, 0x00000050}, {&LPC_SC->PCLKSEL0, 6}},\
						 {LPC_UART2, {&LPC_PINCON->PINSEL4, 0x000A0000}, {&LPC_SC->PCLKSEL1, 16}},\
						 {LPC_UART3, {&LPC_PINCON->PINSEL9, 0x0f000000}, {&LPC_SC->PCLKSEL1, 18}}\
						}
		extern const struct uart_manager_s *const uart_bus_manager_pointer;
	#endif
 #endif
