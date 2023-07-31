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
 * ��ʼ��׼��ʹ�õĴ��ڣ������ö�ռ
 * @param �������
 * @return 
 */ 
unsigned char uart_use(unsigned char fd);

 /*
  *	д����
  * @param �������
  * @param д�����ݻ���
  * @param д�����ߵĳ���
  * @return ʵ��д�����ߵĳ���
  */
unsigned long uart_write(unsigned char fd, const char * buffer, unsigned long size);

 /*
  *	�������л�ȡһ���ַ�
  * @param �������
  * @return �ַ�
  */
char uart_getchar(unsigned char fd);

 /*
  * �������϶�ȡָ�����ȵ�����
  *	@param �������
  * @param ����
  * @param ��ȡ�ĳ���
  * @return ʵ�ʶ�ȡ�ĳ���
  */
unsigned long uart_read(unsigned char fd, char * buffer, unsigned long size);

 /*
  *	������ڻ�����
  * @param �������
  * @param �����߶����ϵ����ݸ��Ƶ��Ļ��棬���ΪNULL��ִֻ���������
  * @param ����size�����Ϊ0��ִֻ���������
  * @return
  */
unsigned long uart_read_clean(unsigned char fd, char * buffer, unsigned long size);

 /*
  *	�ͷ�����
  * @param �������
  */
void uart_release(unsigned char fd);

#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
