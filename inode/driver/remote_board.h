/*
 * remote_board.h
 */

 #ifndef __REMOTE_BOARD_H__
 #define __REMOTE_BOARD_H__

	#include "i2c.h"
	#include "gpio.h"
	#include "file.h"

	#if REMOTE_BOARD_ENABLE

		#ifndef FILE_REMOTE
		 	#define FILE_REMOTE &file_remote,
		#endif
	 	extern const struct file_operation file_remote;
	 
	#endif
	 	
	 #ifndef FILE_REMOTE
	 	#define FILE_REMOTE 
	 #endif

 #endif
