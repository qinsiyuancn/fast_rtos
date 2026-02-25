#ifndef __INIT_H__
#define __INIT_H__

typedef unsigned int (*const init_fun)();

extern unsigned int do_init( const init_fun* init_fun_list, unsigned int size);

#endif
