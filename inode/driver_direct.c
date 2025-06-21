/*
 * driver_direct.c
 * create by qinsiyuan
 *			on 2025-6-7
 */
#include "driver_direct.h"
#include "device_manager.h"

unsigned int driver_read_direct(unsigned int dev, unsigned char *buf, unsigned long count)
{
    return device_recv(dev, buf, count);
}

unsigned int driver_write_direct(unsigned int dev, const unsigned char *buf, unsigned long count)
{
    return device_send(dev, buf, count); 
}

unsigned int driver_start_direct(unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size)
{
    return device_start(dev, send_buffer, send_size, recv_buffer, recv_size); 
}

unsigned char driver_getchar_direct(unsigned int dev)
{
    return device_getchar(dev); 
}

unsigned short driver_getshort_direct(unsigned int dev)
{
    return device_getshort(dev); 
}

unsigned long driver_getlong_direct(unsigned int dev)
{
    return device_getlong(dev); 
}
