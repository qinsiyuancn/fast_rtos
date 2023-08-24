#include "string_bus_manager.h"
#include "string_bus.h"

#define bus_count (sizeof(bus_list) / sizeof(bus_list[0]))

static const struct string_bus* const bus_list[] = BUS_LIST;

unsigned char string_bus_getchar(unsigned int bus, unsigned int dev){
    if (bus < bus_count)
	if (bus_list[bus] -> getchar)
            return bus_list[bus] -> getchar(dev);
    return 0;
}

void string_bus_setchar(unsigned int bus, unsigned int dev, unsigned char data)
{
    if (bus < bus_count)
        if (bus_list[bus] -> setchar)
            bus_list[bus] -> setchar(dev, data);
}

unsigned char string_bus_set_get_char(unsigned int bus, unsigned int dev, unsigned char data)
{
    if (bus < bus_count)
	if (bus_list[bus] -> set_get_char)
            return bus_list[bus] -> set_get_char(dev);
    return 0;
}

unsigned int string_bus_send(unsigned int bus, unsigned int dev, const unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
	if(bus_list[bus] -> send)
            return bus_list[bus] -> send(dev, data, size);
    return 0;
}

unsigned int string_bus_recv(unsigned int bus, unsigned int dev, unsigned char * data, unsigned int size)
{
    if (bus < bus_count)
        if (bus_list[bus] -> recv)
            return bus_list[bus] -> recv(dev, data, size);
    return 0;
}

unsigned int string_bus_send_recv(unsigned int bus, unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if (bus < bus_count)
        if (bus_list[bus] -> send_recv)
            return bus_list[bus] -> send_recv(dev, send_data, send_size, recv_data, recv_size);
    return 0;
}

