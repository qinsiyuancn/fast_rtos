#ifndef __I2C_CPU_H__
#define __I2C_CPU_H__
extern unsigned int i2c_send_recv(unsigned char fd, unsigned char addr, unsigned char * send_data, unsigned int send_size, unsigned char recv_data, unsigned int recv_size);
extern unsigned int i2c_recv(unsigned char fd, unsigned char addr, unsigned char * data, unsigned int size);
extern unsigned int i2c_send(unsigned char fd, unsigned char addr, const unsigned char * data, unsigned int size);
extern unsigned int i2c_stop(unsigned char fd);
extern unsigned int i2c_start(unsigned char fd, unsigned char addr, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size);
extern int i2c_bus_init(unsigned char fd);
extern int i2c_bus_init_all();
#endif
