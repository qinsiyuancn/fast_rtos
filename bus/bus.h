#ifndef __BUS_H__
#define __BUS_H__

struct bus_stream
{
    unsigned int (*const start)(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);
    unsigned int (*const stop) (unsigned int dev);
    unsigned char (* const getchar)(unsigned int dev);
    unsigned short (* const getshort)(unsigned int dev);
    unsigned long (* const getlong)(unsigned int dev);
};


struct bus_buffer
{
    unsigned int (* const send)(unsigned int dev, const unsigned char * data, unsigned int size);
    unsigned int (* const recv)(unsigned int dev, unsigned char * data, unsigned int size);
    unsigned int (* const send_recv)(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);
};

struct bus
{
    const char * const name;
    const struct bus_stream stream;
    const struct bus_buffer buffer;
};

typedef const struct bus * const bus_pointer;

#endif
