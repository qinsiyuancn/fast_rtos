#include "i2c_phy.h"



unsigned char i2c_getchar(unsigned int index , unsigned char slave_addr)
{

}

void i2c_setchar(unsigned int index , unsigned char slave_addr, unsigned char data)
{

}

unsigned char i2c_set_get_char(unsigned int index , unsigned char slave_addr, unsigned char data)
{

}

unsigned int i2c_send(unsigned int index , unsigned char slave_addr, const unsigned char * data, unsigned int size)
{

}

unsigned int i2c_recv(unsigned int index , unsigned char slave_addr, unsigned char * data, unsigned int size)
{

}

unsigned int i2c_send_recv(unsigned int index , unsigned char slave_addr, const unsigned char *send_data, unsigned int send_size, unsigned char *recv_data, unsigned int recv_size)
{

}
