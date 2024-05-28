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
 */
void init_files()
{
    unsigned long i = 0;
    for(i = 0; i < file_count; i++) {
        driver_init(files[i].driver);
    }
}
