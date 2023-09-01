#ifndef __BUS_CTRLER_H__
#define __BUS_CTRLER_H__

struct bus_ctrler
{
    Semaphore finish;
    Locker usingbus;
};

#endif
