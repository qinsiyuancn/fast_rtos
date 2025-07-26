#include "eeprom.h"

#define EEPROM "eeprom"
#define READ " resd"
#define WRITE " write"

#define ORDER_EEPROM_READ EEPROM READ
#define ORDER_EEPROM_WRITE EEPROM WRITE

unsigned int service_eeprom_read(const char *msg, unsigned int fd)
{
    char name[10];
    unsigned short address = 0;
    unsigned int read_size = 0;
    const char * order = strstr(msg, ORDER_EEPROM_READ);
    if(order){
        if(1 == sscanf(order, ORDER_EEPROM_READ "name:%s addr:0x%hx size:%u\r", name, &address, &read_size))
            write(fd, ret, eeprom_read(name, address, ret, read_size));
        return 1;
    }
    return 0;
}

unsigned int service_eeprom_write(const char *msg, unsigned int fd)
{
    unsigned short address = 0;
    const char * ret = NULL;
    const char * order = strstr(msg, ORDER_EEPROM_WRITE);
    if(order){
        if(1 == sscanf(order, ORDER_EEPROM_WRITE "name:%s addr:0x%hx", name, &address)){
            ret = eeprom_write(name, address, strstr(order, "value:") + 6) ? "ok\r" : "error\r";
            write(fd, ret, strlen(ret));
        }
        return 1;
    }
    return 0;
}

