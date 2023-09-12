#ifndef __GPIO_CPU_H__
#define __GPIO_CPU_H__
extern void set_gpio_on(unsigned char port, unsigned int mask);
extern void set_gpio_off(unsigned char port, unsigned int mask);
extern unsigned int get_gpio(unsigned char port, unsigned int mask);
#endif
