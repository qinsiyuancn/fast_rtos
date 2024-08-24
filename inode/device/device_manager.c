#include "device_manager.h"
#include "device.h"
#include "bus_manamger.h"

static struct device device_list[] = DEVICE_LIST;

unsigned int device_start(unsigned int device, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_start(device_list[device].bus, device_list[device].device, send_buffer, send_size, recv_buffer, recv_size) : -1u;
}

unsigned int device_stop(unsigned int device)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_stop(device_list[device].bus, device_list[device].device) : -1u;
}

unsigned char device_getchar(unsigned int device)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_getchar(device_list[device].bus, device_list[device].device) : -1u;
}

unsigned short device_getshort(unsigned int device)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_getshort(device_list[device].bus, device_list[device].device) : -1u;
}

unsigned long device_getlong(unsigned int device)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_getlong(device_list[device].bus, device_list[device].device) : -1u;
}

unsigned int device_send(unsigned int device, unsigned char * buffer, unsigned int count)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_send(device_list[device].bus, device_list[device].device, buffer, count) : -1u;
}

unsigned int device_recv(unsigned int device, unsigned char * buffer, unsigned int count)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_send(device_list[device].bus, device_list[device].device, buffer, count) : -1u;
}

unsigned int device_send_recv(unsigned int device, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    return device < sizeof(device_list) / sizeof(device_list[0]) ? bus_send_recv(device_list[device].bus, device_list[device].device, send_data, send_size, recv_data, recv_size) : -1u;
}
