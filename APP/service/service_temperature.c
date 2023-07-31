/*
 * service_temperature.c
 * create by qinsiyuan
 * 			on 2016-7-15
 * 提供温度服务
 */

 #include "service_temperature.h"
 
 #if TEMPERATURE_ENABLE
	 
	 /*
	  *	获取温度服务
	  * @param 控制端命令
	  * @return 管辖权
	  */
	 int get_temperature(char * msg){
		 	/*
			 * 通过切通道的方式
			 */
			unsigned char channel[] = {0};
		 	unsigned char temperature[2] = {0};
			const char * order = strstr(msg,"read channel");
			if(order){
				if(sscanf(order, "read channel c:0x%hhx temp\r",channel)){
						setdata("temperature_selector", channel, 1);
						getdata("temperature", temperature, 2);
						sprintf(msg, "ch[0x%02x:0x0]:0x%02x.0x%02x\n", *channel,temperature[0], temperature[1]);
				}
				return 1;
			}
		
		return 0;
	 }
#endif

