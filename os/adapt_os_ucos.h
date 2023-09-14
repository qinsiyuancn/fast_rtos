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

// Semaphore
typedef OS_EVENT * Semaphore;
typedef INT8U SemaphoreErrorCode;

#define os_sem_init(semphore, count) semphore = OSSemCreate(count)
#define os_sem_post(semphore) OSSemPost(semphore)
#define os_sem_wait(semphore) OSSemPend(semphore)
#define os_sem_try(semphore)  OSSemAccept(semphore)
#define os_sem_delete(semphore, error_code) do {\
        OSSemDel(semphore, OS_DEL_ALWAYS, &error_code);\
        semphore = NULL;\
    }while(0)

#define os_sem_enable(semphore) semphore
#define os_sem_count(semphore) (semphore->OSEventCnt)
#define os_sem_get_count(count, semphore) count = os_sem_count(semphore)

#endif

#endif
