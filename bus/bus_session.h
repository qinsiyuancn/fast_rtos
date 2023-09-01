#ifndef __BUS_SESSION_H__
#define __BUS_SESSION_H__

#include "bus_ctrler.h"
#include "buffer.h"

struct bus_session
{
    struct bus_ctrler ctrl;
    struct buffer_recv recv;
    struct buffer_send send;
};

#endif
