#include "init_manager.h"
#include "init.h"

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
    const init_fun init_fun[] = {INIT_FUNCTION_LIST};
    return do_init(init_fun, sizeof(init_fun)/sizeof(init_fun[0]));
}
