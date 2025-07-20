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
unsigned  int remote_power_on(unsigned char slot)
{
    return remote_operation(slot, I2C_CMD_POWERON);	 
}

/*
 *
 */
int remote_power_off(unsigned char slot)
{
    return remote_operation(slot, I2C_CMD_POWEROFF);	 
}

/* 
 *
 */
int service_remote_power_on(char *msg)
{
    unsigned char slot = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweron slot");
        if(order){
            if(1 == sscanf(order, "poweron slot:0x%hhx\r", &slot)){
                strcpy(msg,remote_power_on(slot)?"ok\r":"request error\r");
            }
            return 1;
        }
    }
    return 0; 
}

/*
 *
 */
int service_remote_power_off(char *msg)
{
    unsigned char slot = 0;
    const char * order = NULL;
    if(msg){
        order = strstr(msg, "poweroff slot");
        if(order){
            if(1 == sscanf(order, "poweroff slot:0x%hhx\r", &slot)){
                strcpy(msg, remote_power_off(slot)? "ok\r" : "request error\r");
            }
            return 1;
        }
    }
    return 0; 
}

