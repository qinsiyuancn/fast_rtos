#include "eeprom.h"

#define EEPROM "eeprom"
#define READ " resd"
#define WRITE " write"

#define ORDER_EEPROM_READ EEPROM READ
#define ORDER_EEPROM_WRITE EEPROM WRITE

unsigned int service_eeprom_read(const char *msg, char * ret, unsigned int size)
{
    unsigned short address = {0};
    unsigned int read_size = 0;
    const char * order = strstr(msg, ORDER_EEPROM_READ);
    if(order){
        if(1 == sscanf(order, ORDER_EEPROM_READ " addr:0x%hx size:%u\r", &address, &read_size))
            eeprom_read(0, address, ret, read_size);
        return 1;
    }
    return 0;
}

unsigned int service_eeprom_write(const char *msg, const char * ret, unsigned int size)
{
    unsigned short address = 0;
    const char * order = strstr(msg, ORDER_EEPROM_WRITE);
    if(order){
        if(1 == sscanf(order, ORDER_EEPROM_WRITE " addr:0x%hx", &address)){
            strcpy(ret, eeprom_write(0, address, ret) ? "ok\r" : "error\r");
        }
        return 1;
    }
    return 0;
}

