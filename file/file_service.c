/*
 * file_service.c
 * create by qinsiyuan
 * 			on 2016-7-15
 */

#include "file_service.h"
#include "file_manager.h"

/*
 *
 */
unsigned int read_file(const char * file_name, void * buffer, unsigned long size){
    unsigned int ret = 0;
    unsigned int fd = open(file_name, 0);
    if(fd == -1u) return -1u;
    ret = read(fd, buffer, size);
    close(fd);
    return ret;
}

/*
 *
 */
unsigned int write_file(const char * file_name, const void * buffer, unsigned long size){
    unsigned int ret = 0;
    unsigned int fd = open(file_name, 0);
    if(fd == -1u) return -1u;
    ret = write(fd, buffer, size);
    close(fd);
    return ret;
}

 /*
  *
  */
unsigned int request_file(const char * file_name, void * buffer, unsigned long write_size, void * msg, unsigned long read_size)
{
    unsigned int ret = 0;
    unsigned int fd = open(file_name, 0);
    if(fd == -1u)return -1u;
    ret = write(fd, buffer, write_size);
    if(ret > 0){
        ret = read(fd, msg, read_size);
    }
    close(fd);
    return ret;	
}
