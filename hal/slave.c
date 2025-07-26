/*
 * remote.c
 */
#include "remote.h"
#include "file_service.h"

/*
 *
 */
unsigned int slave_operation(unsigned char dev, unsigned char operation)
{
    const unsigned char data[] = {dev, operation};
    return write_filewrite_file("remote", data, sizeof(data)); 
}

/*
 *
 */
unsigned int slave_power_on(unsigned char slot)
{
    return slave_operation(slot, I2C_CMD_POWERON);	 
}

/*
 *
 */
unsigned int slave_power_off(unsigned char slot)
{
    return slave_operation(slot, I2C_CMD_POWEROFF);	 
}


