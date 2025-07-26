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
extern unsigned int request_service(unsigned long fd, const char *msg, char* ret, unsigned int size);

/*
 *
 */
extern unsigned int request_service_duty(const char * msg, char * ret, unsigned int size);

#endif
