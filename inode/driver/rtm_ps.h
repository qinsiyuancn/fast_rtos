/*
 * rtm_ps.h
 * create by qinsiyuan
 * 			on 2016-7-22
 */

 #ifndef __RTM_PS_H__
 #define __RTM_PS_H__
	#include "file.h"
	#include "gpio.h"

	#if RTM_SUPPORT
		extern const struct file_operation file_rtm_ps;
		#ifndef	FILE_RTM_PS
			#define FILE_RTM_PS &file_rtm_ps,
		#endif
	#endif

	#ifndef	FILE_RTM_PS
		#define FILE_RTM_PS
	#endif
 #endif
