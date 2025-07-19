/*
 * file_service.h
 * create by qinsiyuan
 *			on 2016-7-25
 */

#ifndef __FILE_SERVICE_H__
#define __FILE_SERVICE_H__


/*
 *
 */
extern unsigned int read_file(const char * file_name, void * buffer, unsigned long size){

/*
 *
 */
extern unsigned int write_file(const char * file_name, const void * buffer, unsigned long size){
	
/*
 *
 */
extern unsigned int request_file(const char * file_name, void * buffer, unsigned long write_size, void * msg, unsigned long read_size)
#endif
 
