/*
 * slave.h
 */
#ifndef __SLAVE_H__
#define __SLAVE_H__

extern unsigned int slave_operation(unsigned int slot, unsigned char operation);
extern unsigned int slave_power_on(unsigned int slot);
extern unsigned int slave_power_off(unsigned int slot);

#endif
