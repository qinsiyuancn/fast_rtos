#include "driver.h"
#include "driver_direct.h"


static const struct driver driver = {"direct", {NULL, NULL, driver_read_direct, driver_write_direct}, 
	                                       {driver_start_direct, NULL, driver_getchar_direct, driver_getshort_direct, driver_getlong_direct }};

driver_pointer direct = &driver;
