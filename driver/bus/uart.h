/*****************************************************************************
 *   uart.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.27  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __UART_H 
#define __UART_H

#include "uart_lpc17xx.h"
#include "algorithm_queue.h"
#define BUFSIZE		0x40

/*
 * 初始化准备使用的串口，并设置独占
 * @param 总线序号
 * @return 
 */ 
unsigned char uart_use(unsigned char fd);

 /*
  *	写串口
  * @param 总线序号
  * @param 写入数据缓存
  * @param 写入总线的长度
  * @return 实际写入总线的长度
  */
unsigned long uart_write(unsigned char fd, const char * buffer, unsigned long size);

 /*
  *	从总线中获取一个字符
  * @param 总线序号
  * @return 字符
  */
char uart_getchar(unsigned char fd);

 /*
  * 从总线上读取指定长度的数据
  *	@param 总线序号
  * @param 缓存
  * @param 读取的长度
  * @return 实际读取的长度
  */
unsigned long uart_read(unsigned char fd, char * buffer, unsigned long size);

 /*
  *	情况串口缓冲区
  * @param 总线序号
  * @param 将总线队列上的数据复制到的缓存，如果为NULL，只执行清空命令
  * @param 缓存size，如果为0，只执行情况命令
  * @return
  */
unsigned long uart_read_clean(unsigned char fd, char * buffer, unsigned long size);

 /*
  *	释放总线
  * @param 总线序号
  */
void uart_release(unsigned char fd);

#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
