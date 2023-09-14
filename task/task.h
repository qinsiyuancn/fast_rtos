#ifndef __TASK_H__
#define __TASK_H__

#include "os_adapter.h"

struct stack
{
    stack_buffer* const pointer;
    const stask_size size;
};

struct Task
{
    const fun fun;
    const struct stack stack;
    const priority priority;
};

#define define_stack(stack) {stack, sizeof(stack) / sizeof(stack[0])}

#endif
