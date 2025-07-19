/*
 * service_rtm.c
 * ��rtm��ͨѶ����
 */

 #include "service_rtm.h"

 #if RTM_SUPPORT
 
 /*
  *	request���ӳ�
  * ���ļ�������д�Ͷ�֮����ӳ�ʱ��
  */
 static const struct clock tv = {0,0,0,100};
 
 /*
  *	������
  */
 static const char * err_str[] = {
 "OK!\n",
 "format error!\r",
 "request error!\n",	
 };

 /*
  *	��ȡrtm�汾��
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int service_get_rtm_version(char *msg)
 {
	if(strstr(msg, "read rtm version")){
		*msg = 0x1;
		msg[request("rtm", msg, 1, msg, 17, &tv)] = '\0';
		return 1;
	}
	return 0; 
 }

 /*
  *	��ȡrtm���¶�
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int service_get_rtm_temperature(char *msg)
 {
	if(strstr(msg, "read rtm version")){
		*msg = 0x0;
		msg[request("rtm", msg, 1, msg, 17, &tv)] = '\0';
		return 1;
	}
	return 0; 	 
 }

 /*
  *	��ȡrtm��eeprom
  * @param eeprom����ʼ��ַ
  * @param ����eeprom����
  * @param ��Ҫ��ȡ��eeprom�ĳ���
  * @return ִ�н��
  */
 int get_rtm_eeprom(unsigned short addr,char *str, unsigned long size)
 {
 	char order[1 + sizeof(addr) + sizeof(size)] = {0x3};
	if(str){
		*str = 0;
		if(size){
			*((unsigned short *)(order + 1)) = addr;
			*((unsigned long *)(order + 1 + sizeof(addr))) = size;
			return request("rtm", order, sizeof(order), str, size, &tv);
		}
	}
	return 0;	 
 }

 /*
  *	д��rtm��eeprom
  * @param eeprom����ʼ��ַ
  * @param д��eeprom���ݻ���
  * @param д��eeprom�ĳ���
  * @return ִ�н��
  */
 int set_rtm_eeprom(unsigned short addr, char *str, unsigned char size)
 {
 	char order[sizeof(addr) + sizeof(size) + 256] = {0};
	if(str){
		if(size){
			*((unsigned short *)(order + 1)) = addr;
			*((unsigned long *)(order + 1 + sizeof(addr))) = size;
			memcpy(str + sizeof(addr) + sizeof(size), str, size);
			return setdata("rtm", order, size);
		}
	}
	return 0; 
 }

 /*
  *	д���ַ�����rtm��eeprom
  * @param eeprom����ʼ��ַ
  * @param �ַ�������
  * @return ִ�н��
  */
 int set_rtm_eeprom_str(unsigned short addr, char *str)
 {
	return set_rtm_eeprom(addr, str, strlen(str) + 1); 
 }

 /*
  *	��ȡrtm��eeprom�������
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int service_get_rtm_eeprom(char *msg)
 {
 	unsigned short addr = 0;
	unsigned long size = 1;
	const char * order = NULL;
	if(msg){
		order = strstr(msg,"read rtm eeprom");
		if(order){
			if(2 == sscanf(order, "read rtm eeprom addr:0x%hx size:%lu\r", &addr, &size)){	
				msg[get_rtm_eeprom(addr, msg, size)] = '\0';
			}else{
				strcpy(msg, err_str[1]);
			}
			return 1;
		}
	}
	return 0; 
 }

 /*
  *	д��rtm��eeprom�������
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int service_set_rtm_eeprom(char *msg)
 {
 	unsigned short addr = 0;
	char str[256] = {0};
	const char *order = NULL;
 	if(msg){
		order = strstr(msg,"write rtm eeprom");
		if(order){
			if(2 == sscanf(order, "write rtm eeprom addr:0x%hx value:%s\r", &addr, str)){
				if(set_rtm_eeprom_str(addr, str)){
					strcpy(msg, err_str[0]);
				}else{
					strcpy(msg, err_str[2]);
				}
									
			}else{
				strcpy(msg, err_str[1]);			
			}
			return 1;
		}
	}
	return 0; 
 }

 /*
  *	rtm�Ƿ���λ
  * @return �Ƿ���λ
  *			0����λ
  *			1������λ
  */
 unsigned char get_rtm_ps()
 {
	unsigned char ps[] = {0};
	getdata("rtm_ps", ps, 1);
	return *ps;
 }

 /*
  *	rtm�Ƿ���λ�����
  * @param ���ƻ���
  * @return ��Ͻ
  */
 int service_get_rtm_ps(char * msg)
 { 	
	const char * const ret[] = {"on", "off"};
	strcpy(msg, ret[get_rtm_ps()]);
	return 0;
 }

 /*
  *	rtm�Ȳ��֧��
  * ��Ҫ����rtm�Ƿ���λ�����ʹ�ܺ󿨹���
  * �Ա�֤�Ȳ��rtm���Լ�ʱ�ϵ�
  */
 void service_rtm_power()
 {
	unsigned int tmp = 0;
	static unsigned char rtm_state = 2;
	tmp = get_rtm_ps();
	if(tmp != rtm_state){
		rtm_state = tmp;
		set_sys_nrtmen_3_en(tmp);
		OSTimeDlyHMSM(0, 0, 1, 0);
		set_sys_nrtmen_12_en(tmp);
		set_cpld_value(tmp);
	}
 }
 #endif
