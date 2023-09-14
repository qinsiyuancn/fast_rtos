#ifndef __ADAPT_OS_UCOS_H__
#define __ADAPT_OS_UCOS_H__

#if UCOS_II
#include "ucos_ii.h"

// task
typedef void  (*fun) (void *p_arg);
typedef OS_STK stack_buffer;
typedef unsigned int stack_size;
typedef INT8U priority;

#define task_create(task) OSTaskCreate(task.fun, (void*)0, task.stack.pointer + task_list.stack.size - 1, task->priority)

#endif

#endif
