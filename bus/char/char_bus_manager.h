#ifndef __CHAR_BUS_MANAGER_H__
#define __CHAR_BUS_MANAGER_H__

extern unsigned char char_bus_getchar(unsigned int bus, unsigned int dev);

extern void char_bus_setchar(unsigned int bus, unsigned int dev, unsigned char data);

extern unsigned char char_bus_set_get_char(unsigned int bus, unsigned int dev, unsigned char data);

extern void char_bus_start(unsigned int bus, unsigned int dev);

extern void char_bus_stop(unsigned int bus, unsigned int dev);

#endif
