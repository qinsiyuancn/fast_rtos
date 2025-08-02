#include "eeprom.h"

static const char * const name[] = EEPROM_NAME_LIST;
unsigned int service_eeprom_read(unsigned int fd)
{
    char ret[EEPROM_BUFFER_SIZE] = {};
    unsigned int current = 0;
    const unsigned char name_index = getchar(fd);
    unsigned short address = getshort(fd);
    unsigned long read_size = getlong(fd);
    if(name_index < (sizeof(name)/sizeof(name[0]))){
        while(read_size){
            current = eeprom_read(name[name_index], address, ret, read_size < (sizeof(ret)) ? read_size : sizeof(ret));
	    address += current;
            read_size -= write(fd, ret, current);
	}
    }
   return 1;
}

unsigned int service_eeprom_write(unsigned int fd)
{
    unsigned int current = 0;
    unsigned int ret = 0;
    const unsigned char name_index = getchar(fd);
    unsigned short address = getshort(fd);
    unsigned long read_size = getlong(fd);
    unsigned char buffer[EEPROM_BUFFER_SIZE] = {};
    while (read_size)
    {
        current = read(fd, buffer, read_size < sizeof(buffer) ? read_size : sizeof(buffer));
	if(current)break;
        ret = eeprom_write(name[name_index], address,buffer, current);
	if(ret != current)break;
        address += current;
	read_size -= current;
    }
    write(fd, &read_size, sizeof(read_size));
    return 0;
}

