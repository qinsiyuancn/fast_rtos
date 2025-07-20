/*
 * remote.c
 */
#include "remote.h"
#include "file_service.h"

/*
 *
 */
unsigned int remote_operation(unsigned char dev, unsigned char operation)
{
    unsigned char data[2] = {0};
    data[0] = dev;
    data[1] = operation;
    return setdata("remote", data, sizeof(data)); 
}

/*
 *
 */
unsigned int remote_power_on(unsigned char slot)
{
    return remote_operation(slot, I2C_CMD_POWERON);	 
}

/*
 *
 */
unsigned int remote_power_off(unsigned char slot)
{
    return remote_operation(slot, I2C_CMD_POWEROFF);	 
}


