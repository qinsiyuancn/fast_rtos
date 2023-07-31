#include "task_manager.h"
#include "task_config.h"
 #include "ucos_ii.h"
 #include "cpu.h"

static const struct Task * const task_list[] = TASK_LIST;

void start_tasks()
{
	  unsigned int i = 0;
    while(i < (sizeof(task_list) / sizeof(task_list[0])){
			  OSTaskCreate(task_list->fun(), (void*)0, task_list[i].stack.pointer + task_list[i].stack.size - 1, 4 + i);
		    i++;
		}
}