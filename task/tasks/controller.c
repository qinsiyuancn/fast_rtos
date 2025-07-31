#include "controller.h"
#include "task.h"
#include "os_adapter.h"

static task_buffer stack[STACK_CONTROLLER_SIZE]; 

/*
 *
 */
static  void  controller (void *p_arg)
{
    static unsigned char buffer[BUFFER_SIZE];
    static unsigned int i = 0;
    //OS_CPU_SysTickInit();
    static const unsigned int fd = open("ttyS",0);
    start(fd, NULL, 0, NULL, 0);
    while(1){
        i = 0;
        do{
            buffer[i] = getchar(fd);
	}while(buffer[i++] != MESSAGE_END && i != (sizeof(buffer)/sizeof(buffer[0])));
	if(i < (sizeof(buffer)/sizeof(buffer[0])))
            request_string_service_duty(buffer, fd);
        delay(CONTROLLER_TIMER);
    }
}

static const struct Task task = {fun, define_stack(stack), 4};
const struct Task * const controller = &task;
