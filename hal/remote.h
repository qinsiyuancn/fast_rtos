/*
 * service_board.h
 */
#ifndef __REMOTE_H__
#define __REMOTE_H__

enum remote_cmd
{
    power_off,
    poser_on,
    temperature,
};

extern unsigned int remote_operation(unsigned char slot, unsigned char operation);
extern unsigned int remote_power_on(unsigned char slot);
extern unsigned int remote_power_off(unsigned char slot);

#endif
