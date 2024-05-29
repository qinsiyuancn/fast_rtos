/*
 * file_manager.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * 
 */
#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

/*
 * 
 * @param 
 * @param 
 * @return 
 */
extern unsigned int open(const char *, unsigned int );

/*
 * 
 * @param 
 * @param 
 * @param 
 * @return 
 */
extern unsigned int read(unsigned int , unsigned char *, unsigned long );

/*
 *
 * @param 
 * @param 
 * @param 
 * @return 
 */
extern unsigned int write(unsigned int , const unsigned char *, unsigned long );

/*
 * 
 * @param 
 * @param 
 * @param 
 * @return
 */
extern unsigned int ioctl(unsigned int , unsigned int , unsigned long);

/*
 * 
 * @param 
 * @return 
 */
extern unsigned int close(unsigned int );

/*
 * @param fd
 * @param send_buffer
 * @param send_size
 * @param recv_buffer
 * @param recv_size
 * @return
 */
extern unsigned int start(unsigned int fd, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);

/*
 * @param fd
 * @return
 */
extern unsigned int stop(unsigned int fd);

/*
 * @param fd
 * @return
 */
extern unsigned char getchar(unsigned int fd);

/*
 * @param fd
 * @return
 */
extern unsigned short getshort(unsigned int fd);

/*
 * @param fd
 * @return
 */
extern unsigned long getlong(unsigned int fd);

/*
 * 
 */
extern void init_files(void);

#endif
