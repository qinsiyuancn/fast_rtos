/*
 * service_board.c
 * 与其他卡进行通讯服务
 */
 #include "service_board.h"

 #if REMOTE_BOARD_ENABLE

 /*
  *	发送给远程板子的操作
  * @param 远程板子的槽位号
  * @param 请求远程板子的操作
  * @return 执行结果
  */
 int board_operation(unsigned char slot, unsigned char operation)
 {
	unsigned char data[2] = {0};
	data[0] = slot;
	data[1] = operation;
	return setdata("remote_board", data, sizeof(data)); 
 }

 /*
  *	请求远程板子上电
  * @param 远程板子槽位号
  * @return 执行结果
  */
 int board_power_on(unsigned char slot)
 {
	return board_operation(slot, I2C_CMD_POWERON);	 
 }

 /*
  *	请求远程板子下电
  * @param 远程板子的槽位号
  * @return 执行结果
  */
 int board_power_off(unsigned char slot)
 {
	return board_operation(slot, I2C_CMD_POWEROFF);	 
 }

 /*
  *	外服务控制远程板子上电
  * @param 控制缓存
  * @return 管辖
  */
 int service_board_power_on(char *msg)
 {
 	unsigned char slot = 0;
	const char * order = NULL;
	if(msg){
		order = strstr(msg, "poweron slot");
		if(order){
			if(1 == sscanf(order, "poweron slot:0x%hhx\r", &slot)){
				if(board_power_on(slot)){
					strcpy(msg, "ok\r");
				}else{
					strcpy(msg, "request error\r");
				}
			}
			return 1;
		}
	}
	return 0; 
 }

 /*
  *	外服务请求板子下电
  * @param 控制缓存
  * @return 管辖
  */
 int service_board_power_off(char *msg)
 {
 	unsigned char slot = 0;
	const char * order = NULL;
	if(msg){
		order = strstr(msg, "poweroff slot");
		if(order){
			if(1 == sscanf(order, "poweroff slot:0x%hhx\r", &slot)){
				if(board_power_off(slot)){
					strcpy(msg, "ok\r");
				}else{
					strcpy(msg, "request error\r");
				}
				
			}
			return 1;
		}
	}
	return 0; 
 }

 #endif

