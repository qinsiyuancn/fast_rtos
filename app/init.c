#include "init.h"

unsigned int do_init(const init_fun * init_fun_list, unsigned int size)
{
    unsigned int i = 0;
    for (i = 0; i < size; i++)
        init_fun_list[i]();
    return 0;
}
