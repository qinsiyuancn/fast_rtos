/*
 * rtm.h
 * RTMͨѶ
 */

 #ifndef __RTM_H__
 #define __RTM_H__

	#include "file.h"
	#include "i2c.h"
	#if RTM_SUPPORT

		#ifndef FILE_RTM
			#define FILE_RTM &file_rtm,
		#endif

		extern const struct file_operation file_rtm;	
	#endif

	#ifndef FILE_RTM
		#define FILE_RTM
	#endif
 #endif

