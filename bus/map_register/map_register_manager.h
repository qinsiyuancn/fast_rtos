#ifndef __MAP_REGISTER_MANAGER_H__
#define __MAP_REGISTER_MANAGER_H__
extern unsigned char map_register_get_data(unsigned int bus, unsigned int dev);

extern void map_register_set_data(unsigned int bus ,unsigned int dev, unsigned char data);

extern void map_register_clr_data(unsigned int bus, unsigned int dev, unsigned char data);
#endif
