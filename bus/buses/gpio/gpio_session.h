#ifndef __GPIO_SESSION_H__
#define __GPIO_SESSION_H__

#include "bus_session.h"

enum state_bit
{
    write,
    read,
    interrupted,
    setAck
};

struct gpio_config
{
    enum gpio_mode mode;
}

struct gpio_session
{
    const struct config config;
    struct bus_session session;
    unsigned char address;
    unsigned char state_bitmap;
    unsigned char buffer_default[0xff];
    unsigned int current;
    Semaphore queue_size;
};

#define getbit(bitmap, index) ((bitmap >> index) & 0x1)
#define setbit(bitmap, index) bitmap |= (0x1 << index)
#define clrbit(bitmap, index, vaild) bitmap &= ((~(0x1 << index)) & ((0x1 << vaild) - 1))

#endif
