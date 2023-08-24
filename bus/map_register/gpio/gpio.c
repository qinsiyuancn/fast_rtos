#include "map_register.h"
#include "map_register_dev.h"

static struct map_register map_register_list[] = MAP_REGISTER_LIST;

unsigned char get_data(unsigned int dev)
{
    return (map_register_get_data(map_register_list[dev].port) >> map_register_list[dev].offset) && map_register_list[dev].mask;
}

void set_data(unsigned int dev, unsigned char data)
{
    map_register_set_data((map_register_list[dev].port, data && map_register_list[dev].mask) << map_register_list[dev].offset);
}

void clr_data(unsigned int dev, unsigned char data)
{
    map_register_clr_data((map_register_list[dev].port, data && map_register_list[dev].mask) << map_register_list[dev].offset);
}
