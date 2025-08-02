#include "task.h"
#include "os_adapter.h"
#include "file_manager.h"
#include "service_digit_manager.h"

static task_buffer stack[STACK_CONTROLLER_SIZE]; 

/*
 *
 */
static  void  controller (void *p_arg)
{
    //OS_CPU_SysTickInit();
    static const unsigned int fd = open("ttyS",0);
    start(fd, NULL, 0, NULL, 0);
    while(1){
        request_digit_service(getchar(fd), fd);
        delay(CONTROLLER_TIMER);
    }
}

static const struct Task task = {fun, define_stack(stack), 4};
const struct Task * const controller = &task;
