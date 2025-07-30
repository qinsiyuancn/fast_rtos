#include "monitor.h"
#include "task.h"
#include "service_inner_manager.h"

static stack_buffer stack[64]; 

/*
 *
 */
static void fun(void *p_arg)
{
    while(1){
        request_string_service_duty();
        OSTimeDlyHMSM(0, 0, 0, 20);
    }
}

static const struct Task task = {fun, define_stack(stack), 5};
const struct Task * const monitor = &task;
