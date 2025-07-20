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

extern int remote_operation(unsigned char slot, unsigned char operation);
extern int remote_power_on(unsigned char slot);
extern int remote_power_off(unsigned char slot);

extern int service_board_power_on(char *msg);
extern int service_board_power_off(char *msg);

#endif
