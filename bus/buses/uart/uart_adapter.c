#include "uart.h"
#include "uart_cpu.h"

static unsigned int start(unsigned int dev, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    return uart_start(dev, send_buffer, send_size, recv_buffer, recv_size);
}

static unsigned int stop(unsigned int dev)
{
    return uart_stop(dev);
}

static unsigned char getchar(unsigned int dev)
{
    return uart_getchar(dev);
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    if(data && size)
        return uart_send(dev, data, size);
    return 0;
}

static unsigned int recv(unsigned int dev, unsigned char * data, unsigned int size)
{
    if(data && size)
        return uart_recv(dev, data, size);
    return 0;
}

static unsigned int send_recv(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if(send_data && send_size && recv_data && recv_size)
        return uart_send_recv(device_list[dev].bus_index, device_list[dev].slave_addr, send_data, send_size, recv_data, recv_size);
    return 0;
}

static const struct bus bus = {"uart", {start, stop, getchar}, {send, recv, send_recv}};
const struct bus * const uart = &bus;
