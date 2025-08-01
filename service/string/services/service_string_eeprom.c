#include "eeprom.h"

#define EEPROM "eeprom"
#define READ " resd"
#define WRITE " write"

#define ORDER_EEPROM_READ EEPROM READ
#define ORDER_EEPROM_WRITE EEPROM WRITE

unsigned int service_eeprom_read(const char *msg, unsigned int fd)
{
    char name[10];
    unsigned int current = 0;
    unsigned short address = 0;
    unsigned int read_size = 0;
    const char * order = strstr(msg, ORDER_EEPROM_READ);
    char value[EEPROM_BUFFER_SIZE] = {};
    if(order){
        if(1 == sscanf(order, ORDER_EEPROM_READ "name:%s addr:0x%hx size:%u\r", name, &address, &read_size)) {
	    while(read_size){
                current = eeprom_read(name, address, value, read_size < sizeof(value) ? read_size: sizeof(value));
                write(fd, value, current);
		address += current;
		read_size -=current;
	    }
	}
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

