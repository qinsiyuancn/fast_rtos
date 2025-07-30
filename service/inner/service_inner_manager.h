/*
 * service_inner_manager.h
 * create by qinsiyuan
 *			on 2016-7-30
 */

#ifndef __SERVICE_INNER_MANAGER_H__
#define __SERVICE_INNER_MANAGER_H__

/*
 *
 */
extern unsigned int request_inner_service(unsigned long index);

/*
 *
 */
extern unsigned int request_string_service_duty(const char * msg, unsigned int fd);

#endif
