#ifndef __MAP_REGISTER_H__
#define __MAP_REGISTER_H__

struct map_register
{
    unsigned char (*const get_data)(unsigned int bus, unsigned int dev);

    void (* const set_data)(unsigned int bus ,unsigned int dev, unsigned char data);

    void (*const clr_data)(unsigned int bus, unsigned int dev, unsigned char data);

};

#endif
