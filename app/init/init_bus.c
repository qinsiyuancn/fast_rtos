#include "init.h"
#include "bus/bus_manager.h"
static unsigned int init()
{
    extern BUS_INIT_LIST;
    const init_fun init_fun[] = {BUS_INIT_LIST};
    return do_init(init_fun, sizeof(init_fun)/sizeof(init_fun[0]));
}

init_fun init_bus = init;
