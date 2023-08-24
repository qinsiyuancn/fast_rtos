#ifndef __MAP_REGISTER_DEV_H__
#define __MAP_REGISTER_DEV_H__

struct map_register{
    unsigned int port;
    unsigned char offset;
    unsigned char mask;
};

#endif
