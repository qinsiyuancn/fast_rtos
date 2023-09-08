#ifndef __GPIO_CPU_H__
#define __GPIO_CPU_H__
extern unsigned int gpio_send_recv(unsigned char fd, unsigned char addr, unsigned char * send_data, unsigned int send_size, unsigned char recv_data, unsigned int recv_size);
extern unsigned int gpio_recv(unsigned char fd, unsigned char addr, unsigned char * data, unsigned int size);
extern unsigned int gpio_send(unsigned char fd, unsigned char addr, const unsigned char * data, unsigned int size);
extern unsigned int gpio_stop(unsigned char fd);
extern unsigned int gpio_start(unsigned char fd, unsigned char addr, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size);
extern int gpio_bus_init(unsigned char fd);
extern int gpio_bus_init_all();
#endif
