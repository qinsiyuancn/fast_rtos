/*
 * service_inner_manager.c
 * create by qinsiyuan
 *			on 2016-7-30
 */

#include "service_inner_manager.h"

typedef unsigned int (*inner_service)();

extern inner_service SERVICE_LIST;

static inner_service const inner_service_list[] = {SERVICE_LIST};

/*
 *
 */
unsigned int request_inner_service(unsigned long index)
{
    if(index < sizeof(inner_service_list)/sizeof(inner_service_list[0])){
        if(out_service_list[index])
            return out_service_list[index]();
    }
    return 0;
}

/*
 *
 */
unsigned int request_inner_service_duty()
{
    unsigned long i = 0;
    for(i = 0; i < sizeof(inner_service_list)/sizeof(inner_service_list[0]); i++){
	request_inner_service(i);
    }
    return 0;
}

