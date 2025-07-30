#include "controller.h"
#include "task.h"

static task_buffer stack[0x512]; 

/*
 *
 */
static  void  controller (void *p_arg)
{
    unsigned char buffer[40];
    unsigned int i = 0;
    //OS_CPU_SysTickInit();
    const unsigned int fd = open("ttyS",0);
    start(fd, NULL, 0, NULL, 0);
    while(1){
        i = 0;
        do{
            buffer[i] = getchar(fd);
	}while(buffer[i++] != MESSAGE_END);
        request_string_service_duty(buffer, fd);
        OSTimeDlyHMSM(0, 0, 0, 20);
    }
}

static const struct Task task = {fun, define_stack(stack), 4};
const struct Task * const controller = &task;
