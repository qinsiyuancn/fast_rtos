/*
 * service_diag_manager.c
 * create by qinsiyuan
 *             on 2025-07-26
 */

#include "service_diag_manager.h"

typedef unsigned int (*out_service)(unsigned int);

extern out_service SERVICE_LIST;

static out_service const out_service_list[] = {SERVICE_LIST};

unsigned int request_service(unsigned char index, unsigned int fd)
{
    if(index < (sizeof(out_service_list)/sizeof(out_service_list[0])))
        return out_service_list[index](fd);
    return 0;
}
