#include "controller.h"
#include "task.h"

static task_buffer stack[0x512]; 

/*
 *
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
        request_service_duty(buffer, buffer, sizeof(buffer)/sizeof(buffer[0]));
        write(fd,buffer,strlen(buffer));
        OSTimeDlyHMSM(0, 0, 0, 20);
    }
}

static const struct Task task = {fun, define_stack(stack), 4};
const struct Task * const controller = &task;
