#include "driver_manager.h"
#include "driver.h"

extern driver_pointer DRIVER_LIST_INITER;

static driver_pointer list[] = {DRIVER_LIST_INITER};

unsigned int driver_open(unsigned int driver,  unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->open)
                return list[driver]->open(dev);
    return -1u;
}

unsigned int driver_read(unsigned int driver, unsigned int dev, void *buffer, unsigned long size)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->read)
                return list[driver]->read(dev, buffer, size);
    return -1u;
}

unsigned int driver_write(unsigned int driver, unsigned int dev, const void * buffer, unsigned long size)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->write)
                return list[driver]->write(dev, buffer, size);
    return -1u;
}

unsigned int driver_ioctl(unsigned int driver, unsigned int dev, unsigned int request, unsigned long param)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->ioctl)
                return list[driver]->ioctl(dev, request, param);
    return -1u;
}

unsigned int driver_close(unsigned int driver, unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->close)
                return list[driver]->close(dev);
    return -1u;
}

void driver_init(unsigned int driver)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->init)
                list[driver]->init();
}

unsigned int driver_start(unsigned int driver, unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->start)
                return list[driver]->start(dev, send_buffer, send_size, recv_buffer, recv_size);
    return -1u;
}

unsigned int driver_stop(unsigned int driver,unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->stop)
                return list[driver]->stop(dev);
    return -1u;
}

unsigned char driver_getchar(unsigned int driver, unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->getchar)
                return list[driver]->getchar(dev);
    return 0xff;
}

unsigned short driver_getshort(unsigned int driver, unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->getshort)
                return list[driver]->getshort(dev);
    return 0xffff;
}

unsigned long driver_getlong(unsigned int driver, unsigned int dev)
{
    if(driver < (sizeof(list)/sizeof(list[0])))
        if(list[driver])
            if(list[driver]->getlong)
                return list[driver]->getlong(dev);
    return -1ul;
}
