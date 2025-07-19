/*
 * service_board.c
 * ������������ͨѶ����
 */
 #include "service_board.h"

 #if REMOTE_BOARD_ENABLE

 /*
  *	���͸�Զ�̰��ӵĲ���
  * @param Զ�̰��ӵĲ�λ��
  * @param ����Զ�̰��ӵĲ���
  * @return ִ�н��
  */
 int board_operation(unsigned char slot, unsigned char operation)
 {
	unsigned char data[2] = {0};
	data[0] = slot;
	data[1] = operation;
	return setdata("remote_board", data, sizeof(data)); 
 }

 /*
  *	����Զ�̰����ϵ�
  * @param Զ�̰��Ӳ�λ��
  * @return ִ�н��
  */
 int board_power_on(unsigned char slot)
 {
	return board_operation(slot, I2C_CMD_POWERON);	 
 }

 /*
  *	����Զ�̰����µ�
  * @param Զ�̰��ӵĲ�λ��
  * @return ִ�н��
  */
 int board_power_off(unsigned char slot)
 {
	return board_operation(slot, I2C_CMD_POWEROFF);	 
 }

 /*
  *	��������Զ�̰����ϵ�
  * @param ���ƻ���
  * @return ��Ͻ
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
  *	�������������µ�
  * @param ���ƻ���
  * @return ��Ͻ
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

