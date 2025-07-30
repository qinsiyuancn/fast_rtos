/*
 * service_manager.h
 * create by qinsiyuan
 *			on 2016-7-19
 */

#ifndef __SERVICE_STRING_MANAGER_H__
#define __SERVICE_STRING_MANAGER_H__

/*
 *
 */
extern unsigned int request_string_service(unsigned long index, const char *msg, unsigned int fd);

/*
 *
 */
extern unsigned int request_string_service_duty(const char * msg, unsigned int fd);

#endif
