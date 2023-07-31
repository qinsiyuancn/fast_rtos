/*
 * file_manager.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * 文件管理器
 */
#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include "led.h"
#include "slot.h"
#include "sys_dc_12v_en.h"
#include "cpld.h"
#include "sys_nrtmen_3.h"
#include "sys_oren.h"
#include "rtm_ps.h"
#include "sys_nrtmen_12.h"
#include "temperature_selector.h"
#include "temperature.h"
#include "ttyS.h"
#include "shelf.h"
#include "rtm.h"
#include "remote_board.h"
#include "eeprom.h"

/*
 * 文件列表
 */
#define FILE_LIST {&file_ttyS,				\
					&file_led,				 \
					&file_slot,				  \
					&file_sys_dc_12v_en,	   \
					&file_sys_nrtmen_3,			\
					&file_sys_oren,				 \
					FILE_RTM_PS					  \
					&file_sys_nrtmen_12,		   \
					DEVICE_TEMPERATURE				\
					FILE_TEMPERATURE_SELECTOR		 \
					FILE_SHELF			   		  	  \
					FILE_REMOTE						   \
					FILE_RTM							\
					&file_eeprom,						 \
					}


/*
 * 查询指定驱动的的fd
 * 如果查询到，有的驱动可能会被初始化，所以即使知道fd,也尽量先open一下
 * @param 驱动(文件)名称
 * @param 标志
 * @return 文件标示符，如果文件标示符是-1表示没找到查询结果
 */
extern int open(const char *, int );

/*
 * 文件读操作
 * @param 文件标示符
 * @param 读取文件的内容
 * @param 读取文件的长度
 * @return 实际读取的长度
 */
extern int read(int , void *, unsigned long );

/*
 * 文件写操作
 * @param 文件标示符
 * @param 文件写操作缓存
 * @param 写入的长度
 * @return 实际写入的长度
 */
extern int write(int , const void *, unsigned long );

/*
 * 文件操作设置
 * @param 文件标示符
 * @param 设置标志，与具体驱动实现有关
 * @param 设置参数，与具体驱动实现有关
 * @return
 */
extern int ioctl(int , int , void * );

/*
 * 关闭文件
 * @param 文件标示符
 * @return 
 */
extern int close(int );

/*
 * 驱动的初始化
 */
extern void init_files(void);

#endif
