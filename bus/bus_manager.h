#ifndef __BUS_MANAGER_H__
#define __BUS_MANAGER_H__

extern unsigned int bus_start(unsigned int bus, unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);

extern unsigned int bus_stop(unsigned int bus, unsigned int dev);

extern unsigned char bus_getchar(unsigned int bus, unsigned int dev);

extern unsigned short bus_getshort(unsigned int bus, unsigned int dev);

extern unsigned long bus_getlong(unsigned int bus, unsigned int dev);

extern unsigned int bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size);

extern unsigned int bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size);

extern unsigned int bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);

#endif
