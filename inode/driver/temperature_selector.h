/*
 * temperature_selector.h
 * create by qinsiyuan
 *			on 2016-7-22
 */

 #ifndef __TEMPERATURE_SELECTOR_H__
 #define __TEMPERATURE_SELECTOR_H__

	#include "file.h"
	#include "i2c.h"
	#if TEMPERATURE_I2C_MATHOD

		#define TEMPERATURE_SELECTOR_ENABLE_BIT 0x8
		#ifndef FILE_TEMPERATURE_SELECTOR
			#define FILE_TEMPERATURE_SELECTOR &file_temperature_selector,
		#endif
		extern const struct file_operation file_temperature_selector;

	#endif

	#ifndef FILE_TEMPERATURE_SELECTOR
		#define FILE_TEMPERATURE_SELECTOR
	#endif

 #endif
