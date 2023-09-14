#ifndef __BUS_CTRLER_H__
#define __BUS_CTRLER_H__

struct bus_ctrler
{
    FastRtosSemaphore finish;
    FastRtosLocker usingbus;
};

#endif
