/*
 * eeprom.c
 * create by qinsiyuan
 *			on 2016-11-8
 * 提供eeprom读写操作封装
 */

 #include "eeprom.h"
 
 static const char * const eeprom_filename = "eeprom";
 static const struct i2c_device eeprom_i2c = BOARD_EEPROM;

 static int eeprom_open(const char * filename, int flags)
{
	return !strcmp(filename, eeprom_filename);
}

static int eeprom_close()
{
	return 0;
}

/*
 *	buf[0]：设备编号
 *	buf[1,count] 私有协议，不包括两个0xaa
 */
static int eeprom_write(const void *buf, unsigned long count)
{
	i2c_init_master(eeprom_i2c.fd);
	i2c_slave_address(eeprom_i2c.fd, eeprom_i2c.slave_addr);
	return i2c_write(eeprom_i2c.fd, buf, count);	
}

static int eeprom_read(void *buf, unsigned long count)
{
	if(buf){
		if(count){
			i2c_init_master(eeprom_i2c.fd);
			i2c_slave_address(eeprom_i2c.fd, eeprom_i2c.slave_addr);
			return i2c_read(eeprom_i2c.fd, buf, count);
		}
	}
	return 0;
}

static void eeprom_init()
{
		
}

const struct file_operation file_eeprom = {eeprom_init, eeprom_open, eeprom_read, eeprom_write, NULL, eeprom_close};

