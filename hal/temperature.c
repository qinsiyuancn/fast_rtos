/*
 * temperature.c
 * create by qinsiyuan
 * 			on 2016-7-15
 */

#include "temperature.h"
#include "file_manager.h" 

unsigned long get_temperature(const char * name){
    unsigned long ret = 0;
    unsigned int fd = open(name, 0);
    start(fd, NULL, 0, NULL, 0);
    ret = getlong(fd);
    close(fd);
    return ret;
}

