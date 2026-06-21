#include "driver.h"
#include "device_manager.h"

static const struct driver driver = {"direct", NULL, {NULL, driver_recv, device_send}, 
	                                       {device_start, NULL, device_getchar, device_getshort, device_getlong }};

driver_pointer direct = &driver;
