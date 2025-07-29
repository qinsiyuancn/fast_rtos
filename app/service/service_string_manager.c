/*
 * service_manager.c
 * create by qinsiyuan
 *			on 2016-7-19
 */

#include "service_string_manager.h"

typedef unsigned int (*out_service)(const char *, unsigned int);

extern out_service SERVICE_LIST;

static out_service const out_service_list[] = {SERVICE_LIST};

/*
 *
 */
unsigned int request_service(unsigned long index, const char *msg, unsigned int fd)
{
    if(fd < sizeof(out_service_list)/sizeof(out_service_list[0])){
        if(out_service_list[index])
            return out_service_list[index](msg, fd);
    }
    return 0;
}

/*
 *
 */
unsigned int request_service_duty(const char * msg, unsigned int fd)
{
    static const char * const error = "no that service!\r";
    unsigned long i = 0;
    for(i = 0; i < sizeof(out_service_list)/sizeof(out_service_list[0]); i++){
        if(request_service(i, fd)){
            return 1;
        }
    }
    write(fd, error, strlen(error));
    return 0;
}

