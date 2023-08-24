#ifndef __STRING_BUS_H__
#define __STRING_BUS_H__

struct string_bus {
    const char * const name;
    unsigned char (* const getchar)(unsigned int dev);
    void (* const setchar)(unsigned int dev, unsigned char data);
    unsigned char (* const set_get_char)(unsigned int dev, unsigned char data);
    unsigned int (* const send)(unsigned int dev, const unsigned char * data, unsigned int size);
    unsigned int (* const recv)(unsigned int dev, unsigned char * data, unsigned int size);
    unsigned int (* const send_recv)(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);

};
#endif
