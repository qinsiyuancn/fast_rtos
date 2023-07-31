/*
 * service_manager.h
 * create by qinsiyuan
 *			on 2016-7-19
 * 提供对service的服务管理
 * 所有服务需要通过将头文件加入service_manager.h进行注册
 * service分为外服务和内服务
 * 内服务:
 *	1.为上层应用直接提供调用接口
 *	2.接口随意，根据使用方便自由定义
 *	3.无需管理，直接调用函数名称即可
 * 外服务：
 *	1.提供远程服务
 *	2.接口固定类型为：int (*out_service)(char * msg)
 *  3.注册除了需要头文件，还需要将服务名称加入SERVICE_LIST
 *  4.对于可能用不到的服务加入默认值ＮＵＬＬ
 */

 #ifndef __SERVICE_MANAGER_H__
 #define __SERVICE_MANAGER_H__

 #include "service_led.h"
 #include "service_temperature.h"
 #include "service_en.h"
 #include "service_cpld.h"
 #include "service_shelf.h"
 #include "service_soft.h"
 #include "service_rtm.h"
 #include "service_board.h"
 #include "service_eeprom.h"

 /*
  *	外部服务类型
  * 提供远程服务
  * 采用纯责任链模式
  * 0	没有管辖权，交给下一个服务处理
  * 非0	拥有管辖权，完全处理，处理完成直接返回，不再传递给下一个服务
  * @param 传入命令
  * @return 返回责任（管辖权）
  */
 typedef int (*out_service)(char * msg);
					 
 /*
  *	外服务列表
  */
 #define SERVICE_LIST {        \
 	SERVICE_GET_TEMPERATURE     \
 	SERVICE_GET_SLOT		     \
 	SERVICE_READ_FAN 	  		  \
 	SERVICE_SET_FAN_SPEED		   \
	SERVICE_SET_FAN_REBOOT			\
	SERVICE_SET_FAN_PARA			 \
	get_main_version,				  \
	get_sub_version,				   \
	SERVICE_VERSION_MIX					\
	SERVICE_GET_RTM_VERSION				 \
	SERVICE_GET_RTM_TEMPERATURE			  \
	SERVICE_GET_RTM_EEPROM				   \
	SERVICE_SET_RTM_EEPROM					\
	SERVICE_GET_RTM_PS						 \
	SERVICE_BOARD_POWER_ON					  \
	SERVICE_BOARD_POWER_OFF					   \
	service_eeprom_read,						\
	service_eeprom_write,						 \
 }

/*
 * 提供特定服务有效性及服务管辖权
 * @param 指定服务
 * @param 服务参数
 */
int request_service(unsigned long , char *);

/*
 * 轮训可提供的服务
 * @param 服务参数
 */
int request_service_duty(char * msg);

 #endif
