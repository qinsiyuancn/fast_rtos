/*
 * service_eeprom.h
 * create by qinsiyuan
 *			on 2016-11-8
 * 提供eeprom读写服务
 */

 #ifndef __SERVICE_EEPROM_H__
 #define __SERVICE_EEPROM_H__

	#include "file_service.h"

	int service_eeprom_read(char *msg);
	int service_eeprom_write(char *msg);

 #endif

