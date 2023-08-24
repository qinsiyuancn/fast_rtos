#include "driver_manager.h"
#include "driver.h"

static const struct driver list = DRIVER_LIST_INITER;

int driver_open(unsigned int driver, unsigned int bus, unsigned int dev)
{
    if(list[driver].open)
        return list[driver].open(bus,dev);
    return -1;
}

int driver_read(unsigned int driver, unsigned int bus, unsigned int dev, void *buffer, unsigned long size)
{
    if(list[driver].open)
        return list[driver].read(bus, dev, buffer, size);
    return -1;
}

int driver_write(unsigned int driver, unsigned int bus, unsigned int dev, const void * buffer, unsigned long size)
{
    if(list[driver].write)
        return list[driver].write(bus, dev, buffer, size);
    return -1;
}

int driver_ioctl(unsigned int driver, unsigned int bus, unsigned int dev, unsigned int request, unsigned long param)
{
    if(list[driver].ioctl)
        return list[driver].ioctl(bus, dev, request, param);
    return -1;
}

int driver_close(unsigned int driver, unsigned int bus, unsigned int dev)
{
    if(list[driver].close)
        return list[driver].close(bus,dev);
    return -1;
}

void driver_init(unsigned int driver)
{
    if(list[driver].init)
        list[driver].init();
}

