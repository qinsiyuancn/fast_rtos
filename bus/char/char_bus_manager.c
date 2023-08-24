#include "bus_manager.h"
#include "bus.h"

#define bus_count (sizeof(bus_list) / sizeof(bus_list[0]))

static const struct bus* const bus_list[] = BUS_LIST;

unsigned char char_bus_getchar(unsigned int bus, unsigned int dev){
    if (bus < bus_count)
	if (bus_list[bus] -> getchar)
            return bus_list[bus] -> getchar(dev);
    return 0;
}

void char_bus_setchar(unsigned int bus, unsigned int dev, unsigned char data)
{
    if (bus < bus_count)
        if (bus_list[bus] -> setchar)
            bus_list[bus] -> setchar(dev, data);
}

unsigned char char_bus_set_get_char(unsigned int bus, unsigned int dev, unsigned char data)
{
    if (bus < bus_count)
	if (bus_list[bus] -> set_get_char)
            return bus_list[bus] -> set_get_char(dev);
    return 0;
}


void char_bus_start(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus] -> start)
            bus_list[bus] -> start(bus, dev);
}
void char_bus_stop(unsigned int bus, unsigned int dev)
{
    if (bus < bus_count)
        if (bus_list[bus] -> stop)
            bus_list[bus] -> stop(bus, dev);
}
