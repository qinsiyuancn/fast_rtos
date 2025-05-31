#ifndef __BUS_SESSION_H__
#define __BUS_SESSION_H__

#include "bus_ctrler.h"
#include "buffer.h"

struct bus_session
{
    struct bus_ctrler ctrl;
    struct buffer recv;
    struct buffer_ro send;
};

#endif
