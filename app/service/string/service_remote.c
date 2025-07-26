#include "remote.h"
/* 
 *
 */
unsigned int service_remote_power_on(const char *msg, char * ret, unsigned int size)
{
    unsigned char slot = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweron slot");
        if(order){
            if(1 == sscanf(order, "poweron slot:0x%hhx\r", &slot)){
                strncpy(ret,remote_power_on(slot)?"ok\r":"request error\r", size);
            }
            return 1;
        }
    }
    return 0; 
}

/*
 *
 */
unsigned int service_remote_power_off(const char *msg, char * ret, unsigned int size)
{
    unsigned char slot = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweroff slot");
        if(order){
            if(1 == sscanf(order, "poweroff slot:0x%hhx\r", &slot)){
                strncpy(ret, remote_power_off(slot)? "ok\r" : "request error\r", size);
            }
            return 1;
        }
    }
    return 0; 
}

