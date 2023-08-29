#ifndef __I2C_SESSION_H__
#define __I2C_SESSION_H__

enum i2c_mode{
    slave,
    master
};

struct i2c_config
{
    enum i2c_mode mode;
}
struct i2c_ctrler
{
    Semaphore sem;
};

struct i2c_buffer
{
    unsigned int size;
    unsigned int current;
    unsigned char * buffer;
    unsigned char [0xff] default_buffer;
};

struct i2c_session
{
    const struct i2c_config config;
    struct i2c_ctrler ctrler;
    struct i2c_buffer buffer;
};

#endif
