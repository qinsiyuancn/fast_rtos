#include "temperature.h"
#include "file_manager.h"

unsigned int service_get_temperature(unsigned int fd)
{
    static const char* name[] = TEMPERATURE_LIST;
    unsigned char name_index = getchar(fd);
    if(name_index < (sizeof(name)/sizeof(name[0]))){
        unsigned long temperature = get_temperature(name[name_index]);
	write(fd, temperature, sizeof(temperature));
    }
    return 0;
}
