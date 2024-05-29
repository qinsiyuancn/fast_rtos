#include "file_manager.h"
#include "file.h"
#include "driver_manager.h"

#define file_count (sizeof(files)/sizeof(files[0]))

/*
 *  
 */
static const struct files[] = FILE_LIST;

/* 
 * @param 
 * @param flag
 * @return 
 */
unsigned int open(const char *pathname, unsigned int flags)
{
    unsigned int i = 0;
    for(i = 0; i < file_count; i++)
        if(!strcmp(filename, cpld_filename))
            if(driver_open(files[i].driver, files[i].device))	
                return i;
    return -1u;
}

/*
 * 
 * @param fd
 * @param buffer
 * @param buffer size
 * @return 
 */
unsigned int read(unsigned int fd, unsigned char *buf, unsigned long count)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_read(files[fd].driver, files[i].device, buf, count) : 0;
}

/*
 * 
 * @param fd
 * @param 
 * @param 
 * @return 
 */
unsigned int write(unsigned int fd, const unsigned char *buf, unsigned long count)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_write(files[fd].driver, files[fd].device, buf, count) : 0;
}

/*
 * @param fd
 * @param request
 * @param 
 * @return
 */
unsigned int ioctl(unsigned int fd, unsigned int request, unsigned long param)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_ioctl(files[fd].driver, files[fd].device, request, unsigned long param) : 0;
}

/*
 * 
 * @param fd
 * @return 
 */
unsigned int close(unsigned int fd)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_close(files[fd].driver, files[fd].device) : -1u;
}

/*
 *
 * @param fd
 * @param send_buffer
 * @param send_size
 * @param recv_buffer
 * @param recv_size
 */

unsigned int start(unsigned int fd, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_start(files[fd].driver, files[fd].device, send_buffer, send_size, recv_buffer, recv_size) : -1u;
}

/*
 *
 * @param fd
 * @return
 */
unsigned int stop(unsigned int fd)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_stop(files[fd].driver, files[fd].device) : -1u;
}

/*
 * @param fd
 * @return
 */
unsigned char getchar(unsigned int fd)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_getchar(files[fd].driver, files[fd].device) : 0xff;
}

/*
 * @param fd
 * @return
 */
unsigned short getshort(unsigned int fd)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_getshort(files[fd].driver, files[fd].device) : 0xffff;
}

/*
 * @param fd
 * @return
 */
unsigned long getlong(unsigned int fd)
{
    return fd < sizeof(files) / sizeof(files[0]) ? driver_getlong(files[fd].driver, files[fd].device) : -1ul;
}

/*
 * 
 */
void init_files()
{
    unsigned long i = 0;
    for(i = 0; i < file_count; i++) {
        driver_init(files[i].driver);
    }
}
