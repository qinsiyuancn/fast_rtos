#include "init.h"
static unsigned int init()
{
    extern PERIPHERAL_INIT_LIST;
    const init_fun init_fun[] = {PERIPHERAL_INIT_LIST};
    return do_init(init_fun, sizeof(init_fun)/sizeof(init_fun[0]));
}

init_fun init_peripheral = init;
