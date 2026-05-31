#include "init.h"
#include "os_adapter.h"
static unsigned int init()
{
   fast_rtos_init();
   return 0;
}

init_fun init_os = init;
