/*
 * service_soft.c
 * create by qinsiyuan
 *			on 2016-7-19
 * 提供软件服务
 */
 #include "service_soft.h"

 /*
  *	用于板卡无关
  */
 static const char * const main_version = MAIN_VERSION;
 
 /*
  *	用于板卡相关
  */
 static const char * const sub_version = SUB_VERSION;

 /*
  *	获取单一版本号
  * 作为外服务的共同部分调用
  * @param 命令字符串
  * @param 版本字符串
  * @param 控制缓存
  * @return 管辖
  */
 static int get_single_version(const char * charge, const char * version, char * msg)
 {
	if(strstr(msg, charge)){
 		strcpy(msg, version);
		strcat(msg,"\r");
		return 1;
	}
 	return 0; 
 }

 /*
  *	获取主版本号
  * 即硬件无关的版本号
  * @param 控制缓存
  * @return 管辖
  */
 int get_main_version(char *msg)
 {
	return get_single_version("read main_vers\r", main_version, msg);
 }

 /*
  *	获取子版本号
  * 即硬件相关的版本号
  * @param 控制缓存
  * @retur 管辖
  */
 int get_sub_version(char *msg)
 {
	return get_single_version("read sub_vers\r", sub_version, msg);
 }


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
 int get_version(char *msg)
 {
	if(strstr(msg, "read vers\r")){
		strcpy(msg, main_version);
		strcat(msg, " ");
		strcat(msg, sub_version);
		strcat(msg, "\r");
		return 1;
	}
	return 0; 
 }
 #endif
