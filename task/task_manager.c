#include "task_manager.h"
#include "task.h"
#include "task_config.h"
#include "cpu.h"

static const struct Task * const task_list[] = TASK_LIST;

void start_tasks()
{
    unsigned int i = 0;
    while(i < (sizeof(task_list) / sizeof(task_list[0]))) {
        task_create(task_list[i]);
        i++;
    }
}
