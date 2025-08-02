#include "slave.h"
#include "file_manager.h"
/* 
 *
 */
unsigned int service_slave_power_on(unsigned int fd)
{
    unsigned int ret = slave_power_on(getchar(fd));
    write(fd, &ret, sizeof(ret));
    return 0; 
}

/*
 *
 */
unsigned int service_slave_power_off(unsigned int fd)
{
    unsigned int ret = slave_power_off(getchar(fd));
    write(fd, &ret, sizeof(ret));
    return 0; 
}

