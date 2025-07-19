/*
 * driver.h
 * create by qinsiyuan
 *			on 2016-7-22
 */

 #ifndef __DRIVER_H__
 #define __DRIVER_H__

 struct file_operation {
    void (*init)();
    unsigned int (*open)(unsigned int dev);
    unsigned int (*read)(unsigned int dev, unsigned char *buf, unsigned long count);
    unsigned int (*write)(unsigned int dev, const unsigned char *buf, unsigned long count);
    unsigned int (*ioctl)(unsigned int dev, unsigned int request, unsigned long arg);
    unsigned int (*close)(unsigned int dev);

    unsigned int (*start)(unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);
    unsigned int (*stop)(unsigned int dev);
    unsigned char (*getchar)(unsigned int dev);
    unsigned short (*getshort)(unsigned int dev);
    unsigned long (*getlong)(unsigned int dev);
 };

struct driver {
    const char * const name;
    const struct file_operation fops;
};

typedef const struct driver * const driver_pointer;

 #endif
