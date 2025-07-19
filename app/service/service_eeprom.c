/*
 * service_eeprom.c
 * create by qinsiyuan
 *			on 2016-11-8
 * 提供eeprom读写的服务
 */

 #include "service_eeprom.h"
static const struct clock delay = {0,0,0,100};

int service_eeprom_read(char *msg)
{
	unsigned short address[1] = {0};
	const char * order = strstr(msg,"read ipmc eeprom ");
	if(order){
		if(1 == sscanf(order, "read ipmc eeprom addr:0x%hx\r", address)){
			*(unsigned short *)msg = *address;
			msg[request("eeprom", msg, 2, msg, 1, &delay)]='\0';
			sprintf(msg, "%03d\r", msg[0]);			
		}
		return 1;
	}
	return 0;
}

int service_eeprom_write(char *msg)
{
	unsigned short address = 0;
	const char * order = strstr(msg,"write ipmc eeprom ");
	if(order){
		if(1 == sscanf(order, "write ipmc eeprom addr:0x%hx value:", &address)){
			*(1 + strstr(order, "\r")) = 0;
			order = strstr(order, "e:");
			*(unsigned short *)order = address;
			address = 2 + strlen(order + 2);
			if(address == setdata("eeprom", order, address)){
				//strcpy(msg, "ok!\r");
				sprintf(msg, "%03d\r", order[2]);
			}else{
				//strcpy(msg, "set data error\r");
				sprintf(msg, "%03d\r", order[2]);
			}
		}
		return 1;
	}
	return 0;
}

