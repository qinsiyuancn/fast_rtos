#include "init_manager.h"

typedef unsigned int (*const init_fun)();

unsigned int init()
{
/*
    SystemInit();
#if ENA_WDG
    WDInit();
#endif
    OSInit();
*/
    extern init_fun INIT_FUNCTION_LIST;
    unsigned int i = 0;
    init_fun init_fun[] = {INIT_FUNCTION_LIST};
    for(i = 0; i < (sizeof(init_fun)/sizeof(init_fun[])); i++)
        init_fun[i]();
    return 0;
}
