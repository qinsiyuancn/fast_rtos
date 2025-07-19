/*
 * service_shelf.h
 * create by qinsiyuan
 *			on 2016-7-25
 */

 #ifndef __SERVICE_SHELF_H__
 #define __SERVICE_SHELF_H__
	#include "file_service.h"

	#if SHELF_ENABLE
		//服务
		#ifndef SERVICE_GET_SLOT
			#define SERVICE_GET_SLOT get_slot_msg,
		#endif

		#ifndef SERVICE_READ_FAN
			#define SERVICE_READ_FAN read_fan,
		#endif

		#ifndef SERVICE_SET_FAN_SPEED
			#define SERVICE_SET_FAN_SPEED set_fan_speed,
		#endif

		#ifndef SERVICE_SET_FAN_REBOOT
			#define SERVICE_SET_FAN_REBOOT set_fan_reboot,
		#endif

		#ifndef SERVICE_SET_FAN_PARA
			#define SERVICE_SET_FAN_PARA set_fan_para,
		#endif

	
		#define ERR_NULL_POINTER 1
		#define ERR_NO_FAN_INDEX 2
		#define ERR_CONVERT 	 3
		#define ERR_FAN_INDEX_ILLEGAL	4
		#define ERR_NO_FAN_CMD	 5
		#define ERR_NO_CNT		 6
		#define ERR_I2C_TRANSMIT 7
		#define ERR_FORMATING_DATA 8
		#define ERR_NO_VALUE     9
	
		#define  set_crc(c) c |= 1 << 7

		/*
		 * 获取槽位服务
		 * @return 槽位号
		 */
		unsigned char get_slot(void);

		/*
		 * 获取槽位的外服务
		 * @param 从串口读取的命令，返回槽位信息
		 * @return 管辖
		 */
		int get_slot_msg(char * );

		/*
		 * 读取风扇信息
		 * @param 串口命令，返回风扇信息
		 * @param 管辖
		 */
		int read_fan(char * );

		/*
		 * 设置风扇速度
		 * @param 串口命令，返回执行情况
		 * @return 管辖
		 */  
		int set_fan_speed(char * );

		/*
		 * 请求风扇重启
		 * 通常用于设置默认参数
		 * @param 串口命令和返回执行结果
		 * @return 管辖
		 */
		int set_fan_reboot(char * );

		/*
		 * 设置风扇默认参数
		 * 设置后不会立即生效，需要调用重启后生效
		 * @param 串口命令和返回执行结果
		 * @return 管辖
		 */
		int set_fan_para(char * );
	#endif

	#ifndef SERVICE_GET_SLOT
		#define SERVICE_GET_SLOT
	#endif

	 #ifndef SERVICE_READ_FAN
		#define SERVICE_READ_FAN 
	 #endif
	
	 #ifndef SERVICE_SET_FAN_SPEED
		#define SERVICE_SET_FAN_SPEED
	 #endif
	
	 #ifndef SERVICE_SET_FAN_REBOOT
		#define SERVICE_SET_FAN_REBOOT
	 #endif
	
	 #ifndef SERVICE_SET_FAN_PARA
		#define SERVICE_SET_FAN_PARA
	 #endif
 #endif
 
