#include "task_manager.h"
#include "os_adapter.h"

int main(void)
{
    init();
    start_tasks();
    fast_rtos_start();
    return 0;
}



