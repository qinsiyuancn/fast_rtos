#ifndef __GPIO_H__
#define __GPIO_H__
extern void set_gpio_on(unsigned char port, unsigned int mask);
extern void set_gpio_off(unsigned char port, unsigned int mask);
extern unsigned int get_gpio(unsigned char port, unsigned int mask);
#endif
