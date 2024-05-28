#ifndef __DRIVER_MANAGER__
#define __DRIVER_MANAGER__

extern unsigned int driver_open(unsigned int driver, unsigned int dev);

extern unsigned int driver_read(unsigned int driver, unsigned int dev, void *buffer, unsigned long size);

extern unsigned int driver_write(unsigned int driver, unsigned int dev, const void * buffer, unsigned long size);

extern unsigned int driver_ioctl(unsigned int driver, unsigned int dev, int , void *);

extern unsigned int driver_close(unsigned int driver, unsigned int dev);

extern void driver_init(unsigned int driver);

#endif
