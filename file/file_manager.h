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
 * 
 */
extern void init_files(void);

#endif
