#include "init.h"
#include "file_manager.h"
static unsigned int init()
{
    init_files();
    return 0;
}

init_fun init_peripheral = init;
