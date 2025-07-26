/*
 * eeprom.c
 * create by qinsiyuan
 *			on 2016-11-8
 */

#include "eeprom.h"

static const char * const name[] = EEPROM_NAME;

unsigned int eeprom_read(unsigned int dev, unsigned short address, char * data, unsigned int size)
{
    if(data && size)
        return request_file(name[dev], (unsigned char *)&address, 2, (unsigned char *)data, size);
    return 0;
}

unsigned int eeprom_write(unsigned int dev, unsigned short address, const char *data, unsigned int size)
{
    if(data && size)
        return request_file(name[dev], (unsigned char *)&address, 2, (const unsigned char *)data, size);
    return 0;
}

