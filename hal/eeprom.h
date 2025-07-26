/*
 * service_eeprom.h
 * create by qinsiyuan
 *			on 2016-11-8
 */

#ifndef __SERVICE_EEPROM_H__
#define __SERVICE_EEPROM_H__


extern unsigned int eeprom_read(unsigned int dev, unsigned short address, char * data, unsigned int size);
extern unsigned int eeprom_write(unsigned int dev, unsigned short address, const char *data, unsigned int size);

#endif

