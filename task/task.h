#ifndef __TASK_H__
#define __TASK_H__

#include "os_adapter.h"

struct Stack
{
    FastRtosStackBuffer* const pointer;
    const FastRtosStaskSize size;
};

struct Task
{
    const FastRtosFun fun;
    const struct Stack stack;
    const FastRtosPriority priority;
};

#define define_stack(stack) {stack, sizeof(stack) / sizeof(stack[0])}

#endif
