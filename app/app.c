#include "task_manager.h"
#include "service_manager.h"
#include "ucos_ii.h"
#include "cpu.h"

int main(void)
{ 
    init();
    start_tasks();
    OSStart();

}



