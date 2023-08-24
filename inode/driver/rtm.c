/*
 * rtm.c
 * 
 */

 #include "rtm.h"

 #if RTM_SUPPORT
 static const char * const rtm_filename = "rtm";
 static const struct i2c_device rtm_i2c = BOARD_RTM;

 static int rtm_open(const char * filename, int flags)
 {
	return !strcmp(filename, rtm_filename);
 }

 static int rtm_close()
 {
	return 0;
 }

 static int rtm_write(const void *buf, unsigned long count)
 {
	if(buf && count){
		i2c_init_master(rtm_i2c.fd);
		i2c_slave_address(rtm_i2c.fd, rtm_i2c.slave_addr);
		return i2c_write(rtm_i2c.fd, buf, count);
	}

	return 0;	
 }

 static int rtm_read(void *buf, unsigned long count)
 {
	if(buf && count){
		i2c_init_master(rtm_i2c.fd);
		i2c_slave_address(rtm_i2c.fd, rtm_i2c.slave_addr);
		return i2c_read(rtm_i2c.fd, buf, count);
	}
	return 0;
 }

 const struct file_operation file_rtm = {NULL, rtm_open, rtm_read, rtm_write, NULL, rtm_close};
 #endif
