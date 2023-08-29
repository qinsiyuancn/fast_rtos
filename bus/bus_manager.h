#ifndef __BUS_MANAGER_H__
#define __BUS_MANAGER_H__

#define bus_set_bit(bus, dev) bus_setchar(bus, dev, 1)
#define bus_clr_bit(bus, dev) bus_setchar(bus, dev, 0)

extern void bus_start(unsigned int bus, unsigned int dev);

extern void bus_stop(unsigned int bus, unsigned int dev);

extern unsigned char bus_getchar(unsigned int bus, unsigned int dev);

extern void bus_setchar(unsigned int bus, unsigned int dev, unsigned char data);

extern unsigned char bus_set_get_char(unsigned int bus, unsigned int dev, unsigned char data);

extern unsigned int bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size);

extern unsigned int bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size);

extern unsigned int bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);

#endif
