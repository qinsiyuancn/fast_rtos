#ifndef __DRIVER_MANAGER__
#define __DRIVER_MANAGER__

extern int driver_open(unsigned int driver, unsigned int bus, unsigned int dev);

extern int driver_read(unsigned int driver, unsigned int bus, unsigned int dev, void *buffer, unsigned long size);

extern int driver_write(unsigned int driver, unsigned int bus, unsigned int dev, const void * buffer, unsigned long size);

extern int driver_ioctl(unsigned int driver, unsigned int bus, unsigned int dev, int , void *);

extern int driver_close(unsigned int driver, unsigned int bus, unsigned int dev);

extern void driver_init(unsigned int driver);

#endif
