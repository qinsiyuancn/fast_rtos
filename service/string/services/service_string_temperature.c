#include "temperature.h"
#include "file_manager.h"

unsigned int service_get_temperature(const char *msg, unsigned int fd)
{
    char ret[20] = {};
    const char * order = NULL;
    unsigned int temperature = 0;
    if (msg) {
        order = strstr(msg, "temperature");
        if(order){
            order = strstr(order, "name:") + 5;
	    temperature = get_temperature(order);
	    sprintf(ret, "%f\r", (float)temperature / 1000);
	    write(fd, ret, strlen(ret));
        }
    }
    return 0;
}
