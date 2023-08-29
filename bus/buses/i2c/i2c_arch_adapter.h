#ifndef __I2C_ARCH_ADAPTER_H__
#define __I2C_ARCH_ADAPTER_H__

extern unsigned char i2c_getchar(unsigned int index , unsigned char slave_addr);

extern unsigned void i2c_setchar(unsigned int index , unsigned char slave_addr, unsigned char data);

extern unsigned int i2c_send(unsigned int index , unsigned char slave_addr, const unsigned char * data, unsigned int size);

extern unsigned int i2c_recv(unsigned int index , unsigned char slave_addr, unsigned char * data, unsigned int size);

extern unsigned int i2c_send_recv(unsigned int index , unsigned char slave_addr, const unsigned char *send_data, unsigned int send_size, unsigned char *recv_data, unsigned int recv_size);

#endif
