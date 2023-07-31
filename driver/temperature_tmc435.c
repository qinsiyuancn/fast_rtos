/*
 * temperature_tmc435.c
 * create by qinsiyuan
 *			on 2016-7-9 
 *
 * ÎÂ¶È´«¸ÐÆ÷
 */
 #include "temperature_tmc435.h"
 #if DEVICE_TMC435

static const char * const temperature_filename = "temperature";

static const struct i2c_device temperature_i2c[] = BOARD_TEMPERATURE;
static unsigned char cdev = 0;
static int temperature_open(const char * filename, int flags)
{
	return !strcmp(filename, temperature_filename);	
}

static int temperature_close()
{
	return 0;
}

static int temperature_write(const void *buf, unsigned long count)
{
	cdev = 0;
	if(buf){
		if(count){
			cdev = *((unsigned char *)buf);
			if(cdev >= sizeof(temperature_i2c)/ sizeof(temperature_i2c[0])){			
				cdev = 0;
			}
		}
	}
	i2c_init_master(temperature_i2c[cdev].fd);
	return 1;		
}
static int temperature_read(void *buf, unsigned long count)
{
	const char remote[] = {1};
	if(!buf)return 0;
	if(count < 2)return 0;	
	i2c_slave_address(temperature_i2c[cdev].fd, temperature_i2c[cdev].slave_addr);
	i2c_write(temperature_i2c[cdev].fd, remote, 1);	
	i2c_read(temperature_i2c[cdev].fd, buf, 2);
	return 2;
}

const struct file_operation file_temperature_tmc435 = {NULL, temperature_open, temperature_read, temperature_write, NULL, temperature_close};
#endif
