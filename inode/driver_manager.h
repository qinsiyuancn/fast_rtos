#ifndef __DRIVER_MANAGER__
#define __DRIVER_MANAGER__

extern unsigned int driver_open(unsigned int driver, unsigned int dev);

extern unsigned int driver_read(unsigned int driver, unsigned int dev, void *buffer, unsigned long size);

extern unsigned int driver_write(unsigned int driver, unsigned int dev, const void * buffer, unsigned long size);

extern unsigned int driver_ioctl(unsigned int driver, unsigned int dev, int , void *);

extern unsigned int driver_close(unsigned int driver, unsigned int dev);

extern void driver_init(unsigned int driver);

extern unsigned int driver_start(unsigned int driver, unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);

extern unsigned int driver_stop(unsigned int driver, unsigned int dev);

extern unsigned char driver_getchar(unsigned int driver, unsigned int dev);

extern unsigned short driver_getshort(unsigned int driver, unsigned int dev);

extern unsigned long driver_getlong(unsigned int driver, unsigned int dev);

#endif
