#include "map_register.h"
#include "map_register_dev.h"
#define count (sizeof(list)/sizeof(list[0]))
static const struct map_register *const list[] = MAP_REGISTER_LIST;

unsigned char map_register_get_data(unsigned int bus, unsigned int dev)
{
    if(bus < count)
        if(list[bus]->get_data)
            return list[bus]->get_data(dev);
    return 0;
}

void map_register_set_data(unsigned int bus, unsigned int dev, unsigned char data)
{
    if(bus < count)
        if(list[bus]->set_data)
            return list[bus]->set_data(dev, data);
}

void map_register_clr_data(unsigned int bus, unsigned int dev, unsigned char data)
{
    if(bus < count)
        if(list[bus]->clr_data)
            return list[bus]->clr_data(dev, data);
}

void map_register_clr_bit(unsigned int bus, unsigned int dev, unsigned char pos)
{
    map_register_clr_data(bus, dev, 0x1 << pos);
}

void map_register_set_bit(unsigned int bus, unsigned int dev, unsigned char pos)
{
    map_register_set_data(bus, dev, 0x1 << pos);
}
