#ifndef __ADAPT_OS_H__
#define __ADAPT_OS_H__

#if UCOS_II
#include "ucos_ii.h"

// task
typedef void  (*FastRtosFun) (void *p_arg);
typedef OS_STK FastRtosStackBuffer;
typedef unsigned int FastRtosStackSize;
typedef INT8U FastRtosPriority;
typedef INT8U ErrorCode;

#define fast_rtos_task_create(task) OSTaskCreate(task->fun, (void*)0, task->stack.pointer + task->stack.size - 1, task->priority)

// Semaphore
typedef OS_EVENT * FastRtosSemaphore;
typedef INT8U FastRtosSemaphoreErrorCode;

#define fast_rtos_sem_init(semphore, count) semphore = OSSemCreate(count)
#define fast_rtos_sem_post(semphore) OSSemPost(semphore)
#define fast_rtos_sem_wait(semphore) OSSemPend(semphore)
#define fast_rtos_sem_try(semphore)  OSSemAccept(semphore)
#define fast_rtos_sem_deinit(semphore, error_code) do {\
        OSSemDel(semphore, OS_DEL_ALWAYS, error_code);\
        semphore = NULL;\
    }while(0)

#define fast_rtos_sem_enable(semphore) semphore
#define fast_rtos_sem_count(semphore) (semphore->OSEventCnt)
#define fast_rtos_sem_get_count(count, semphore) count = fast_rtos_sem_count(semphore)

// locker
#define fast_rtos_mutex_init(mutex, priority, error_code) mutex = OSMutextCreate(priority, &error_code)
#define fast_rtos_mutex_lock(mutex, timeout, error_code) OSMutexPend(mutex, timeput, &error_code)
#define fast_rtos_mutex_unlock(mutex) OSMutexPost(mutex)
#define fast_rtos_mutex_deinit(mutex, error_code) OSMutexDel(mutex, OS_DEL_ALWAYS, &error_code)

#define delay(time) OSTimeDlyHMSM(time)

#define fast_rtos_start() OSStart()

#endif

#endif
