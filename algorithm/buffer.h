#ifndef __BUFFER_H__
#define __BUFFER_H__

struct buffer
{
    unsigned int size;
    unsigned char * buffer;
};

struct buffer_ro
{
    unsigned int size;
    const unsigned char * buffer;
};

#endif
