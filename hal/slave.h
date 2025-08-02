/*
 * slave.h
 */
#ifndef __SLAVE_H__
#define __SLAVE_H__

extern unsigned int slave_operation(unsigned char slot, unsigned char operation);
extern unsigned int slave_power_on(unsigned char slot);
extern unsigned int slave_power_off(unsigned char slot);

#endif
