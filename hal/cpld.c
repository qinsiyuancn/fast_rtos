/*
 * cpld.c
 * create by qinsiyuan
 * 			on 2016-7-18
 */
#include "service_cpld.h"
#include "file_service.h"

 /*
  *
  */
void set_cpld_value(unsigned char v)
{
    write_file("cpld", &v, 1);
}
 
/*
 *
 */
void cpld_set()
{
    set_cpld_value(1);
}

 /*
  *
  */
void cpld_clr()
{
    set_cpld_value(0);
}

