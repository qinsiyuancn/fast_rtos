/*
 * eeprom.c
 * create by qinsiyuan
 *			on 2016-11-8
 */

#include "eeprom.h"

static const char * const name[] = EEPROM_NAME;

unsigned int eeprom_read(unsigned int dev, unsigned short address, unsigned char * data, unsigned int size)
{
    if(data && size)
        return request_file(name[dev], (unsigned char *)&address, 2, data, size);
    return 0;
}

unsigned int eeprom_write(unsigned int dev, unsigned short address, const unsigned char *data, unsigned int size)
{
    if(data && size)
        return request_file(dev, (unsigned char *)&address, 2, data, size);
    return 1;
}


int service_eeprom_read(char *msg)
{
    unsigned short address[1] = {0};
    const char * order = strstr(msg,"read ipmc eeprom ");
    if(order){
        if(1 == sscanf(order, "read ipmc eeprom addr:0x%hx\r", address)){
            *(unsigned short *)msg = *address;
            sprintf(msg, "%03d\r", msg[0]);			
        }
     return 1;
    }
    return 0;
}

int service_eeprom_write(char *msg)
{
    unsigned short address = 0;
    const char * order = strstr(msg,"write ipmc eeprom ");
    if(order){
        if(1 == sscanf(order, "write ipmc eeprom addr:0x%hx value:", &address)){
            *(1 + strstr(order, "\r")) = 0;
            order = strstr(order, "e:");
            *(unsigned short *)order = address;
            address = 2 + strlen(order + 2);
            if(address == setdata("eeprom", order, address)){
                //strcpy(msg, "ok!\r");
                sprintf(msg, "%03d\r", order[2]);
            }else{
                //strcpy(msg, "set data error\r");
                sprintf(msg, "%03d\r", order[2]);
            }
        }
        return 1;
    }
    return 0;
}

