#include "uart_lpc17xx.h"

#if CPU_lpc17xx

extern void uart_irq_handler(unsigned char fd);

/*****************************************************************************
** Function name:		cpu_uart_init/UARTInit
**
** Descriptions:		Initialize UART port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			 fd and UART baudrate
** Returned value:		true or false, return false only if the 
**						interrupt handler can't be installed to the 
**						VIC table
** 
*****************************************************************************/
extern int cpu_uart_init(unsigned char fd, unsigned long baudrate);

/*****************************************************************************
** Function name:		cpu_uart_send/UARTSend
**
** Descriptions:		Send a block of data to the UART 0 port based
**						on the data length
**
** parameters:			 fd, buffer pointer, and data length
** Returned value:		None
** 
*****************************************************************************/
extern unsigned char cpu_uart_send( unsigned char fd, unsigned char c);

#endif
/******************************************************************************
**                            End Of File
******************************************************************************/
