#include "remote.h"
/* 
 *
 */
unsigned int service_remote_power_on(const char *msg, unsigned int fd)
{
    const char * ret = NULL;
    unsigned int slave = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweron slave");
        if(order){
            if(1 == sscanf(order, "poweron slave:%u\r", &slave)){
                ret = slave_power_on(slave) ? "ok\r" : "request error\r";
		write(fd, ret, strlen(ret));
            }
            return 1;
        }
    }
    return 0; 
}

/*
 *
 */
unsigned int service_remote_power_off(const char *msg, unsigned int fd)
{
    const char * ret = NULL;
    unsigned int slave = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweroff slave");
        if(order){
            if(1 == sscanf(order, "poweroff slave:%u\r", &slave)){
                ret = slave_power_off(slave)? "ok\r" : "request error\r";
		write(fd, ret, strlen(ret));
            }
            return 1;
        }
    }
    return 0; 
}

