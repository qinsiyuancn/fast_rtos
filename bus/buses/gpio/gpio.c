#include "gpio.h"
#include "gpio_dev.h"
#include "gpio_cpu.h"
#define dev_size (sizeof(device_list) / sizeof(device_list[0]))

static  struct i2c_device device_list[] = I2C_DEV_LIST;

static unsigned int start(unsigned int dev, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    if(dev < dev_size)
        return gpio_start(device_list[dev].bus_index, device_list[dev].slave_addr, send_buffer, send_size, recv_buffer, recv_size);
    return 1;
}

static unsigned int stop(unsigned int dev)
{
    if(dev < dev_size)
        return gpio_stop(device_list[dev].bus_index);
    return 1;
}

static unsigned char getchar(unsigned int dev)
{
    if(dev < dev_size)
        return gpio_getchar(device_list[dev].bus_index);
    return 0;
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    if(dev < dev_size)
        return gpio_send(device_list[dev].bus_index, device_list[dev].slave_addr, data, size);
    return 0;
}

static unsigned int recv(unsigned int dev, unsigned char * data, unsigned int size)
{
    if(dev < dev_size)
        return gpio_recv(device_list[dev].bus_index, device_list[dev].slave_addr, data, size);
    return 0;
}

static unsigned int send_recv(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if(dev < dev_size)
        return gpio_send_recv(device_list[dev].bus_index, device_list[dev].slave_addr, send_data, send_size, recv_data, recv_size);
    return 0;
}

static const struct bus bus = {"gpio", {start, stop, getchar}, {send, recv, send_recv}};
const struct bus * const gpio = &bus;