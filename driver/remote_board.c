/*
 * remote_board.c
 */

 #include "remote_board.h"

 #if REMOTE_BOARD_ENABLE

 static const unsigned char remote_i2c_fd = REMOTE_I2C_FD;
 static const char * const remote_filename = "remote_board";
 static const struct {const unsigned char port; const unsigned char pos;}i2c_enable = IPMB_BUFFER_EN;//临时放到这里，将来要单独封装到一个文件中
 
 static int remote_open(const char * filename, int flags)
 {
	return !strcmp(filename, remote_filename);
 }

 static int remote_close()
 {
	return 0;
 }

 static int remote_write(const void *buf, unsigned long count)
 {
	if(buf && count){
		i2c_init_master(remote_i2c_fd);
		i2c_slave_address(remote_i2c_fd, *(const unsigned char *)buf);
		return i2c_write(remote_i2c_fd, ((const char *)buf + 1), count - 1);
	}

	return 0;	
 }
 #if 0
 static int remote_read(void *buf, unsigned long count)
 {
	if(buf && count){
		return i2c_read(remote_i2c_fd, buf, count);
	}
	return 0;
 }
 #endif
 static void remote_init()
 {
	set_gpio_bit_on(i2c_enable.port, i2c_enable.pos);	
 }

 const struct file_operation file_remote = {remote_init, remote_open, NULL, remote_write, NULL, remote_close}; 	
	 
 #endif
