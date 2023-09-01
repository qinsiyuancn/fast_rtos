#include "bus_manager.h"
#include "bus.h"

#define bus_count (sizeof(bus_list) / sizeof(bus_list[0]))

static const struct bus* const bus_list[] = BUS_LIST;

unsigned char bus_getchar(unsigned int bus, unsigned int dev){
    if (bus < bus_count)
	if (bus_list[bus].char_op -> getchar)
            return bus_list[bus].char_op -> getchar(dev);
    return 0;
}

unsigned int bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
	if(bus_list[bus].string_op -> send)
            return bus_list[bus].string_op -> send(dev, data, size);
    return 0;
}

unsigned int bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
        if (bus_list[bus].string_op -> recv)
            return bus_list[bus].string_op -> recv(dev, data, size);
    return 0;
}

unsigned int bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if (bus < bus_count)
        if (bus_list[bus].string_op -> send_recv)
            return bus_list[bus].string_op -> send_recv(dev, send_data, send_size, recv_data, recv_size);
    return 0;
}

void bus_start(unsigned int bus, unsigned int dev, unsigned char * send_buffer, unsigned int send_size)
{
    if (bus < bus_count)
        if (bus_list[bus].char_op -> start)
            bus_list[bus].char_op -> start(bus, dev, send_buffer, send_size);
}
void bus_stop(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus].char_op -> stop)
            bus_list[bus].char_op -> stop(bus, dev);
}

