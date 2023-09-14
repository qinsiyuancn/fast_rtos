#ifndef __ADAPT_OS_UCOS_H__
#define __ADAPT_OS_UCOS_H__

#if UCOS_II
#include "ucos_ii.h"

// task
typedef void  (*FastRtosFun) (void *p_arg);
typedef OS_STK FastRtosStackBuffer;
typedef unsigned int FastRtosStackSize;
typedef INT8U FastRtosPriority;

#define fast_rtos_task_create(task) OSTaskCreate(task.fun, (void*)0, task.stack.pointer + task_list.stack.size - 1, task->priority)

// Semaphore
typedef OS_EVENT * FastRtosSemaphore;
typedef INT8U FastRtosSemaphoreErrorCode;

#define fast_rtos_sem_init(semphore, count) semphore = OSSemCreate(count)
#define fast_rtos_sem_post(semphore) OSSemPost(semphore)
#define fast_rtos_sem_wait(semphore) OSSemPend(semphore)
#define fast_rtos_sem_try(semphore)  OSSemAccept(semphore)
#define fast_rtos_sem_delete(semphore, error_code) do {\
        OSSemDel(semphore, OS_DEL_ALWAYS, &error_code);\
        semphore = NULL;\
    }while(0)

#define fast_rtos_sem_enable(semphore) semphore
#define fast_rtos_sem_count(semphore) (semphore->OSEventCnt)
#define fast_rtos_sem_get_count(count, semphore) count = os_sem_count(semphore)

#endif

#endif
