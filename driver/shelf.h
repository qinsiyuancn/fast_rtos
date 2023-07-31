/*
 * shelf.h
 * create by qinsiyuan
 *			on 2016-7-22
 */

 #ifndef __SHELF_H__
 #define __SHELF_H__

	#include "file.h"
	#include "i2c.h"
	#include "gpio.h"

	#if SHELF_ENABLE
		#ifndef FILE_SHELF
			#define FILE_SHELF &file_shelf,
		#endif	
		extern const struct file_operation file_shelf;
	#endif

	#ifndef FILE_SHELF
		#define FILE_SHELF
	#endif
 #endif
