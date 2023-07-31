/*
 * temperature_selector.c
 * create by qinsiyuan
 * 			on 2016-7-13
 * 温度选择器
 * 对应硬件的i2c的channel
 * 由于温度传感器地址一样，所以中间有一个选择具体channel的器件
 * 在TEMPERATURE_I2C_MATHOD设置为TEMPERATURE_I2C_MATHOD_CHANNEL时使用
 */
 #include "temperature_selector.h"
#if TEMPERATURE_I2C_MATHOD 
static const char * const temperature_selector_filename = "temperature_selector";

static const struct i2c_device temperature_selector_i2c = BOARD_TEMPERATURE_SELECTER;
static int temperature_selector_open(const char * filename, int flags)
{
	if(strcmp(filename, temperature_selector_filename)){
		return 0;
	}
	i2c_init_master(temperature_selector_i2c.fd);
	return 1;
}

static int temperature_selector_close()
{
	return 0;
}

static int temperature_selector_write(const void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	i2c_slave_address(temperature_selector_i2c.fd, temperature_selector_i2c.slave_addr);
	*((char *)buf) |= TEMPERATURE_SELECTOR_ENABLE_BIT;	
	return i2c_write(temperature_selector_i2c.fd, buf, 1);
}

const struct file_operation file_temperature_selector = {NULL, temperature_selector_open, NULL, temperature_selector_write, NULL, temperature_selector_close};
#endif
