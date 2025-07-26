/*
 * slave.c
 */
#include "slave.h"
#include "file_service.h"

#define REMOTE_POWERON 1
#define REMOTE_POWEROFF 0

/*
 *
 */
unsigned int slave_operation(unsigned char slave, unsigned char operation)
{
    const unsigned char data[] = {dev, operation};
    return write_filewrite_file("slave", data, sizeof(data)); 
}

/*
 *
 */
unsigned int slave_power_on(unsigned int slave)
{
    return slave_operation(slave, REMOTE_POWERON);	 
}

/*
 *
 */
unsigned int slave_power_off(unsigned int slave)
{
    return slave_operation(slave, REMOTE_POWEROFF);	 
}


