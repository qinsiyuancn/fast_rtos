#ifndef __BUS_H__
#define __BUS_H__

struct char_bus {
    void (*const start)(unsigned int dev);
    void (*const stop) (unsigned int dev);
    unsigned char (* const getchar)(unsigned int dev);
    void (* const setchar)(unsigned int dev, unsigned char data);
    unsigned char (* const set_get_char)(unsigned int dev, unsigned char data);
};


struct string_bus {
    unsigned int (* const send)(unsigned int dev, const unsigned char * data, unsigned int size);
    unsigned int (* const recv)(unsigned int dev, unsigned char * data, unsigned int size);
    unsigned int (* const send_recv)(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);
};

struct bus
{
    const char * const name;
    const struct char_bus char_op;
    const struct string_bus string_op;
};

#endif
