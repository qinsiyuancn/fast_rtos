#ifndef __I2C_SESSION_H__
#define __I2C_SESSION_H__

#include "bus_session.h"

enum i2c_mode
{
    slave,
    master
};

enum state_bit
{
    write,
    read,
    interrupted,
    setAck
};

struct i2c_config
{
    enum i2c_mode mode;
}

struct i2c_session
{
    const struct config config;
    struct bus_session session;
    unsigned char address;
    unsigned char state_bitmap;
    unsigned char buffer_default[0xff];
};

#define getbit(bitmap, index) ((bitmap >> index) & 0x1)
#define setbit(bitmap, index) bitmap |= (0x1 << index)
#define clrbit(bitmap, index, vaild) bitmap &= ((~(0x1 << index)) & ((0x1 << vaild) - 1))

#endif
