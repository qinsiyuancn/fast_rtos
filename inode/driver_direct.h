/*
 * driver_direct.h
 * create by qinsiyuan
 *			on 2025-6-7
 */
#ifndef __DRIVER_DIRECT_H__
#define __DRIVER_DIRECT_H__

extern unsigned int driver_read_direct(unsigned int dev, unsigned char *buf, unsigned long count);

extern unsigned int driver_write_direct(unsigned int dev, const unsigned char *buf, unsigned long count);

extern unsigned int driver_start_direct(unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);

extern unsigned char driver_getchar_direct(unsigned int dev); 

extern unsigned short driver_getshort_direct(unsigned int dev); 

extern unsigned long driver_getlong_direct(unsigned int dev); 

#endif
