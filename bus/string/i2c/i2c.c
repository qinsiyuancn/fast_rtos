#include "i2c.h"
#include "bus.h"
#include "i2c_dev.h"
#define dev_size (sizeof(device_list) / sizeof(device_list[0]))
static  struct i2c_device device_list[] = I2C_DEV_LIST;
static unsigned char getchar(unsigned int dev)
{
    if(dev < dev_size)
        return i2c_getchar(device_list[dev].bus_index, device_list[dev].slave_addr);
    return 0;
}

static unsigned void setchar(unsigned int dev, unsigned char data)
{
    if(dev < dev_size)
        i2c_setchar(device_list[dev].bus_index, device_list[dev].slave_addr, data);
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    if(dev < dev_size)
        return i2c_send(device_list[dev].bus_index, device_list[dev].slave_addr, data, size);
    return 0;
}

static unsigned int recv(unsigned int dev, unsigned char * data, unsigned int size)
{
    if(dev < dev_size)
        return i2c_recv(device_list[dev].bus_index, device_list[dev].slave_addr, data, size);
    return 0;
}

static unsigned int send_recv(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if(dev < dev_size)
        return i2c_send_recv(device_list[dev].bus_index, device_list[dev].slave_addr, send_data, send_size, recv_data, recv_size);
    return 0;
}

static const struct bus bus = {"i2c", getchar, setchar, send, recv, send_recv};
const struct bus * const i2c = &bus;
