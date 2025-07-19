/*
 * service_rtm.c
 * 与rtm的通讯服务
 */

 #include "service_rtm.h"

 #if RTM_SUPPORT
 
 /*
  *	request的延迟
  * 即文件操作的写和读之间的延迟时间
  */
 static const struct clock tv = {0,0,0,100};
 
 /*
  *	处理结果
  */
 static const char * err_str[] = {
 "OK!\n",
 "format error!\r",
 "request error!\n",	
 };

 /*
  *	获取rtm版本号
  * @param 控制缓存
  * @return 管辖
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
  *	获取rtm的温度
  * @param 控制缓存
  * @return 管辖
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
  *	获取rtm的eeprom
  * @param eeprom的起始地址
  * @param 返回eeprom缓存
  * @param 需要获取的eeprom的长度
  * @return 执行结果
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
  *	写入rtm的eeprom
  * @param eeprom的起始地址
  * @param 写入eeprom内容缓存
  * @param 写入eeprom的长度
  * @return 执行结果
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
  *	写入字符串到rtm的eeprom
  * @param eeprom的起始地址
  * @param 字符串缓存
  * @return 执行结果
  */
 int set_rtm_eeprom_str(unsigned short addr, char *str)
 {
	return set_rtm_eeprom(addr, str, strlen(str) + 1); 
 }

 /*
  *	获取rtm的eeprom的外服务
  * @param 控制缓存
  * @return 管辖
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
  *	写入rtm的eeprom的外服务
  * @param 控制缓存
  * @return 管辖
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
  *	rtm是否在位
  * @return 是否在位
  *			0：在位
  *			1：不在位
  */
 unsigned char get_rtm_ps()
 {
	unsigned char ps[] = {0};
	getdata("rtm_ps", ps, 1);
	return *ps;
 }

 /*
  *	rtm是否在位外服务
  * @param 控制缓存
  * @return 管辖
  */
 int service_get_rtm_ps(char * msg)
 { 	
	const char * const ret[] = {"on", "off"};
	strcpy(msg, ret[get_rtm_ps()]);
	return 0;
 }

 /*
  *	rtm热插拔支持
  * 需要根据rtm是否在位的情况使能后卡供电
  * 以保证热插拔rtm可以及时上电
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
