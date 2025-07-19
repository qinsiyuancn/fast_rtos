/*
 * i2c_hub.c
 * create by qinsiyuan
 * 			on 2016-7-13
 */

#include "driver.h"


static unsigned int write(unsigned int dev, const unsigned char *buf, unsigned long count)
{
    if (buf && count) {
        unsigned char b = *buf | TEMPERATURE_SELECTOR_ENABLE_BIT;
        return device_send(dev, b, 1);
    }
    return 0;
}

static const struct driver driver = {"i2c_hub", NULL,{ NULL, NULL, write}};
driver_pointer i2c_hub = &driver;
