#ifndef __CHAR_BUS_H__
#define __CHAR_BUS_H__

struct char_bus {
    const char * const name;
    unsigned char (* const getchar)(unsigned int dev);
    void (* const setchar)(unsigned int dev, unsigned char data);
    unsigned char (* const set_get_char)(unsigned int dev, unsigned char data);
    void (*const start)(unsigned int dev);
    void (*const stop) (unsigned int dev);
};
#endif
