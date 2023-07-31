#include "controller.h"

static 	 OS_STK stack[0x512]; 

/*
 * 监控控制端发过来的命令
 */
static  void  controller (void *p_arg)
{
	int fd = 0;
	char buffer [0x40] = {0};
	OS_CPU_SysTickInit();
	fd = open("ttyS",0);
	ioctl(fd, 3, (char *)'\r');
	while(1){
		read(fd, buffer, sizeof(buffer)/sizeof(buffer[0]));
		request_service_duty(buffer);
		write(fd,buffer,strlen(buffer));
		// 线程睡眠20ms,释放CPU
		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}

static const struct Task task = {fun, {stack, (sizeof(stack)/sizeof(stack[0]))}};
const struct Task * const controller = &task;