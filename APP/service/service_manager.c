/*
 * service_manager.c
 * create by qinsiyuan
 *			on 2016-7-19
 * 提供服务列表
 */

#include "service_manager.h"
static const out_service out_service_list[] = SERVICE_LIST;

/*
 * 直接调用外服务
 * @param 外服务编号：即外服务在服务管理器中的位置
 * @param 控制端的命令
 * @return 是否找到外服务
 *			1：找到
 *			0：没找到
 */
int request_service(unsigned long fd, char *msg)
{
	if(fd < sizeof(out_service_list)/sizeof(out_service_list[0])){
		if(out_service_list[fd])
			return out_service_list[fd](msg);
	}
	return 0; 
}
/*
 * 寻找外服务
 * 利用责任链模式，找到管辖的外服务
 * @param 控制端的命令
 * @return 是否找到外服务
 *			1：找到
 *			0：没找到
 */
int request_service_duty(char * msg)
{
	unsigned long i = 0;
	for(i = 0; i < sizeof(out_service_list)/sizeof(out_service_list[0]); i++){
		if(request_service(i, msg)){
			return 1;
		}
	}
	#if SERVICE_RESPOUNCE
		strcpy(msg,"no that service!\r");
	#else
		msg[0] = '\0';
	#endif
	return 0;
}

