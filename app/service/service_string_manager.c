/*
 * service_manager.c
 * create by qinsiyuan
 *			on 2016-7-19
 */

#include "service_string_manager.h"

typedef unsigned int (*out_service)(const char * msg, char * ret, unsigned int size);

extern out_service SERVICE_LIST;

static out_service const out_service_list[] = {SERVICE_LIST};

/*
 *
 */
unsigned int request_service(unsigned long fd, const char *msg, char* ret, unsigned int size)
{
    if(fd < sizeof(out_service_list)/sizeof(out_service_list[0])){
        if(out_service_list[fd])
            return out_service_list[fd](msg, ret, size);
    }
    return 0; 
}

/*
 *
 */
unsigned int request_service_duty(char * msg, char * ret, unsigned int size)
{
    unsigned long i = 0;
    for(i = 0; i < sizeof(out_service_list)/sizeof(out_service_list[0]); i++){
        if(request_service(i, msg, size)){
            return 1;
        }
    }
    strncpy(ret, "no that service!\r", size);
    return 0;
}

