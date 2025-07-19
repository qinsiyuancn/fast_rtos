/*
 * service_manager.c
 * create by qinsiyuan
 *			on 2016-7-19
 * �ṩ�����б�
 */

#include "service_manager.h"
static const out_service out_service_list[] = SERVICE_LIST;

/*
 * ֱ�ӵ��������
 * @param ������ţ���������ڷ���������е�λ��
 * @param ���ƶ˵�����
 * @return �Ƿ��ҵ������
 *			1���ҵ�
 *			0��û�ҵ�
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
 * Ѱ�������
 * ����������ģʽ���ҵ���Ͻ�������
 * @param ���ƶ˵�����
 * @return �Ƿ��ҵ������
 *			1���ҵ�
 *			0��û�ҵ�
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

