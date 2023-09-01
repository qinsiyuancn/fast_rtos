#ifndef __BUFFER_H__
#define __BUFFER_H__

struct buffer_recv
{
    unsigned int size;
    unsigned char * buffer;
};

struct buffer_send
{
    unsigned int size;
    const unsigned char * buffer;
};

#endif
