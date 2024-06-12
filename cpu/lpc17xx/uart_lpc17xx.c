/*****************************************************************************
*   uart.c:  UART API file for NXP LPC17xx Family Microprocessors
*
*   Copyright(C) 2009, NXP Semiconductor
*   All rights reserved.
*
*   History
*   2009.05.27  ver 1.00    Prelimnary version, first Release
*
******************************************************************************/
#include "uart_lpc17xx.h"

#if CPU_lpc17xx
static const struct {
    LPC_UART_TypeDef * const bus_register;
    const struct {
        volatile uint32_t * const selector_p;
        const unsigned int selector_v;
    }pin;
}uart_bus[] = UART_BUS_INIT;

static int irq_IIR_THRE(unsigned char fd, unsigned char state)
{
    volatile unsigned char LSRValue = uart_bus[fd].bus_register->LSR;	
    if ( LSRValue & LSR_THRE ){
        //发送阻塞放行
        return uart_on_transport_finish(uart_bus_manager_pointer, fd);	
    }
    return 0;
}

static int irq_IIR_RDA(unsigned char fd, unsigned char state)
{
    return uart_on_recv_char(uart_bus_manager_pointer ,fd , uart_bus[fd].bus_register->RBR );	
}

static int irq_IIR_RLS(unsigned char fd, unsigned char state)
{
    unsigned char LSRValue = uart_bus[fd].bus_register->LSR;
    /* Receive Line Status */
    if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) ) {
        /* There are errors or break interrupt */
        /* Read LSR will clear the interrupt */
        // UART0Status = LSRValue;
        LSRValue = uart_bus[fd].bus_register->RBR;		/* Dummy read on RX to clear 
        interrupt, then bail out */
    }else if ( LSRValue & LSR_RDR ) /* Receive Data Ready */ {
        /* If no error on RLS, normal ready, save into the data buffer. */
        /* Note: read RBR will clear the interrupt */
        irq_IIR_RDA(fd,state);
    }
    return 0;
}


void uart_irq_handler(unsigned char fd)
{
    static irq_funp const request_irq[6] = {NULL,irq_IIR_THRE,irq_IIR_RDA, irq_IIR_RLS};
    const uint32_t state = (uart_bus[fd].bus_register->IIR >> 1) & 0x07;
    if(request_irq[state])
        request_irq[state](fd, state);
}


/*****************************************************************************
** Function name:		UARTInit
**
** Descriptions:		Initialize UART port, setup pin select,
**						clock, parity, stop bits, FIFO, etc.
**
** parameters:			 fd(0 or 1) and UART baudrate
** Returned value:		true or false, return false only if the 
**						interrupt handler can't be installed to the 
**						VIC table
** 
*****************************************************************************/
int cpu_uart_init( unsigned char fd, unsigned long baudrate )
{
    static const unsigned char div[] = {4,1,2,8};
    uint32_t Fdiv;
    const enum IRQn irqn[] = {UART0_IRQn, UART2_IRQn, UART3_IRQn};
    *(volatile unsigned int *)0x400FC0C4 |= 0X1 << 24;
    LPC_PINCON->PINSEL0 &= ~0x000000F0;
    *uart_bus[fd].pin.selector_p |= uart_bus[fd].pin.selector_v;//LPC_PINCON->PINSEL0 = 0x00000050\LPC_PINCON->PINSEL4=0x000A0000\LPC_PINCON->PINSEL9=0x0f000000;  /* RxD0 is P0.3 and TxD0 is P0.2 */

    Fdiv = (SystemFrequency/div[(*uart_bus[fd].pclock.pointer >> uart_bus[fd].pclock.pos) & 0x03])/ 16 / baudrate;//LPC_SC->PCLKSEL0 >> 6,LPC_SC->PCLKSEL1 >> 16,LPC_SC->PCLKSEL1 >> 18 

    uart_bus[fd].bus_register->LCR = 0x83;		/* 8 bits, no Parity, 1 Stop bit */
    uart_bus[fd].bus_register->DLM = Fdiv / 256;							
    uart_bus[fd].bus_register->DLL = Fdiv % 256;
    uart_bus[fd].bus_register->LCR = 0x03;		/* DLAB = 0 */
    uart_bus[fd].bus_register->FCR = 0x07;		/* Enable and reset TX and RX FIFO. */
	
    NVIC_EnableIRQ(irqn[fd]);

    uart_bus[fd].bus_register->IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable UART0 interrupt */

    return (TRUE);
}

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
unsigned char cpu_uart_send( unsigned char fd, unsigned char c)
{
    uart_bus[fd].bus_register->THR = c;
    return 0;
}

#endif
/******************************************************************************
**                            End Of File
******************************************************************************/
