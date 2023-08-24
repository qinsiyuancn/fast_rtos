#ifndef __STRING_BUS_MANAGER_H__
#define __STRING_BUS_MANAGER_H__

extern unsigned char string_bus_getchar(unsigned int bus, unsigned int dev);
extern void string_bus_setchar(unsigned int bus, unsigned int dev, unsigned char data);
extern unsigned char string_bus_set_get_char(unsigned int bus, unsigned int dev, unsigned char data);
extern unsigned int string_bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size);
extern unsigned int string_bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size);
extern unsigned int string_bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);

#endif
