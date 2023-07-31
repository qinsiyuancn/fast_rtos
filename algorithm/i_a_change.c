/*
 * i_a_change.c
 * 实现字符串与数字之间的转换
 */
 #include "i_a_change.h"
 static const char const * HexNum[] = {"0123456789abcdef", "0123456789ABCDEF"};

 unsigned int cs_sscanf(const char * str){
 	unsigned int i = 0;
	unsigned int ret = 0;
	str = strstr(str, "0x");
	if(str){
		str += 2;
		do{
			for(i = 0; HexNum[1][i] && HexNum[0][i];i++){
				if(*str == HexNum[0][i] || *str == HexNum[1][i]){
					ret = (ret << 4) + i;
					break;
				}
			}
		}while(*(++str));
	}
 	return ret;
 }