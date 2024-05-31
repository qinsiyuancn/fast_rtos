#include "bus_manager.h"
#include "bus.h"

#define bus_count (sizeof(bus_list) / sizeof(bus_list[0]))

static const struct bus* const bus_list[] = BUS_LIST;

unsigned char bus_getchar(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> stream.getchar)
                return bus_list[bus] -> stream.getchar(dev);
    return 0;
}

unsigned short bus_getshort(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> stream.getchar)
                return bus_list[bus] -> stream.getshort(dev);
    /*
     * 这个表达需要根据端序发生改变
     * 先暂时用这个占个位置，后续用宏函数屏蔽差异
     */
    return bus_getchar(bus, dev) << sizeof(unsigned char) | bus_getchar(bus, dev);
}

unsigned long bus_getlong(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> stream.getchar)
                return bus_list[bus] -> stream.getlong(dev);
    /*
     * 这个表达需要根据端序发生改变
     * 先暂时用这个占个位置，后续用宏函数屏蔽差异
     */
    return bus_getchar(bus, dev) << sizeof(unsigned short) | bus_getchar(bus, dev);
}

unsigned int bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> buffer.send)
                return bus_list[bus] -> buffer.send(dev, data, size);
    return 0;
}

unsigned int bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> buffer.recv)
                return bus_list[bus] -> buffer.recv(dev, data, size);
    return 0;
}

unsigned int bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    /*
     * 如果这个函数有自己的实现
     */
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> buffer.send_recv)
                return bus_list[bus] -> buffer.send_recv(dev, send_data, send_size, recv_data, recv_size);

    /*
     * 默认实现
     */
    do {
        unsigned int ret = 0;
        ret = bus_send(bus, dev, send_data, send_size);
        if (!ret) return ret;
    } while(0);

    return bus_recv(bus, dev, recv_data, recv_size);
}

unsigned int bus_start(unsigned int bus, unsigned int dev, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> stream.start)
                return bus_list[bus] -> stream.start(bus, dev, send_buffer, send_size, recv_buffer, recv_size);
    return 1;
}

unsigned int bus_stop(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus])
            if (bus_list[bus] -> stream.stop)
                return bus_list[bus] -> stream.stop(bus, dev);
    return 1;
}
