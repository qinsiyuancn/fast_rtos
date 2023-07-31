/*
 * service_soft.h
 * create by qinsiyuan
 *			on 2016-7-26
 */

 #ifndef __SERVICE_SOFT_H__
 #define __SERVICE_SOFT_H__

	#include "file_service.h"
	
	/*
	 * 主版本号
	 * 用于硬件无关部分的版本号
	 */
	#define MAIN_VERSION "2016-11-8"
	
	/*
	 * 获取主版本号
	 * 即硬件无关的版本号
	 * @param 控制缓存
	 * @return 管辖
	 */
	int get_main_version(char *msg);

	/*
	 * 获取子版本号
	 * 即硬件相关的版本号
	 * @param 控制缓存
	 * @retur 管辖
	 */
	int get_sub_version(char *msg);

	#if VERSION_MIX_ENABLE
	  
	  /*
	   * 混合版本号
	   * 同时返回主版本号和子版本号
	   * 为了兼容之前的客户端保留
	   * 客户端修改后，这个开关就可以关掉了
	   * 这个函数能不用尽量不用
	   * @param 控制缓存
	   * @return 管辖
	   */
		int get_version(char *msg);
		#define SERVICE_VERSION_MIX get_version,
	#else
		#define SERVICE_VERSION_MIX
	#endif

 #endif
 
