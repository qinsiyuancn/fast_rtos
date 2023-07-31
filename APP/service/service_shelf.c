/*
 * service_shelf.c
 * create by qinsiyuan
 *			on 2016-7-18
 * �ṩipmc����佻������
 */

 #include "service_shelf.h"
 
 #if SHELF_ENABLE

 /*
  *	��ȡ��λ����
  * @return ��λ��
  */
 unsigned char get_slot()
 {
 	unsigned char tmp[] = {0};
	getdata("slot", tmp, 1);
	return *tmp;
 }

 /*
  *	��ȡ��λ�������
  * @param �Ӵ��ڶ�ȡ��������ز�λ��Ϣ
  * @return ��Ͻ
  */
 int get_slot_msg(char * msg)
 {
 	unsigned char slot_id = 0;
 	if(strstr(msg, "read slotid\r")){
		slot_id = get_slot();
		strcpy(msg ,"0x00");
		msg[4] = slot_id >> 4;
		msg[5] = slot_id & 0xF;
		if(msg[4] < 0xa)
			msg[4] += 0x30;
		else
			msg[4] += 0x37;

		if(msg[5] < 0xa)
			msg[5] += 0x30;
		else
			msg[5] += 0x37;
		strcpy(msg + 6, "\r");
		return 1;
	}
	return 0;	
 }

 /*
  *	��ȡ������Ϣ
  *	@param ����������ط�����Ϣ
  * @return ��Ͻ
  */
 int read_fan(char * msg)
 {
 	const struct clock tv = {0,0,0,100};
	char buf[5] = {0};
	unsigned char buffer[] = {0,0};
	unsigned char rd_cnt = 0;
	unsigned char i = 0;
	unsigned char index = 0;
 	const char * order = strstr(msg, "read fan");
	if(order){
		if(sscanf(order, "read fan i:0x%hhx cmd:0x%hhx r_cnt:0x%hhu\r", buffer, buffer + 1, &rd_cnt)==3){
			if(rd_cnt > sizeof(buf)/sizeof(buf[0]))	rd_cnt = sizeof(buf)/sizeof(buf[0]);//��ֹ���������
			request("shelf", buffer, 2, buf, rd_cnt, &tv);
			for(i = 0; i < rd_cnt; i++) {
				index += sprintf(msg + index, "0x%02x ", *(buf + i));
			}
			*(msg + index) = '\n';
		}else{
			strcpy(msg, "format error!\n");
		}
		return 1;
	}
	return 0;
 }
 
 /*
  *	���÷����ٶ�
  * @param �����������ִ�����
  *	@return ��Ͻ
  */   
 int set_fan_speed(char * msg)
 {
 	unsigned char buffer[] = {0, 0x10, 0x3, 0x0, 0x0};
	const char * order = strstr(msg,"write fan speed");
	if(order){
		if(sscanf(order ,"write fan speed i:0x%hhx val:0x%hhx\r", buffer, buffer + 4) == 2){
			set_crc(*buffer);
			if(setdata("shelf", buffer, 5) == 5)
				strcpy(msg, "ok\r");
			else
				strcpy(msg, "set data error\r");
			
		}else
			strcpy(msg, "format error!\n");
		return 1;
	}
	return 0;
 }

 /*
  *	�����������
  * ͨ����������Ĭ�ϲ���
  * @param ��������ͷ���ִ�н��
  * @return ��Ͻ
  */
 int set_fan_reboot(char * msg)
 {
 	unsigned char buffer []	= {0, 0x13};
 	const char * order = strstr(msg , "fan reboot");
	if(order){
		if(sscanf(order, "fan reboot i:0x%hhx\r", buffer) == 1){
			set_crc(*buffer);
			if(2 == setdata("shelf", buffer, 2))
				strcpy(msg, "ok!\n");
			else
				strcpy(msg, "Fail!\n");
		}else{
			strcpy(msg, "format error!\n");
		}
		return 1;
	}
	return 0;
 }
 
 /*
  * ���÷���Ĭ�ϲ���
  * ���ú󲻻�������Ч����Ҫ������������Ч
  * @param ��������ͷ���ִ�н��
  * @return ��Ͻ
  */
 int set_fan_para(char * msg)
 {
 	unsigned char buffer []	= {0, 0x14, 0xb, 0, 0, 0x40, 0x42, 0x44, 0x46, 0, 0, 0, 0};
	const char * order = strstr(msg, "set fan para");
	if(order){
		if(6 == sscanf(order, "set fan para i:0x%hhx val:0x%hhx:0x%hhx:0x%hhx:0x%hhx:0x%hhx\r",
		 buffer, buffer + 3, buffer + 4, buffer + 9, buffer + 10, buffer + 11)){
			set_crc(*buffer);
			if(sizeof(buffer) == setdata("shelf", buffer, sizeof(buffer)))
				strcpy(msg, "ok!\n");
			else{
				strcpy(msg, "set data error!\n");
			}
			
		}else{
			strcpy(msg, "format error!\n");
		}
		return 1;
	}
	return 0;
 }
 #endif 
