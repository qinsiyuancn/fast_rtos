#include "gpio_adapter.h"
#include "gpio_dev.h"
#include "gpio.h"
#define dev_size (sizeof(device_list) / sizeof(device_list[0]))

static  struct gpio_device device_list[] = I2C_DEV_LIST;

static unsigned char getchar(unsigned int dev)
{
    if(dev < dev_size)
        return 0 != get_gpio(device_list[dev].port, 0x1 << device_list[dev].offset);
    return 0;
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    static void (* const set_gpio_operation)[](unsigned char port, unsigned int mask) = {
       set_gpio_off,
       set_gpio_on,
    };
    if(dev < dev_size)
        if(data && size > 1) {
            if(data[0] < (sizeof(set_gpio_operation)/sizeof(set_gpio_operation[0])))
                return gpio_send(device_list[dev].port, 0x1 << device_list[dev].offset, data[1]);
    return 0;
}
static unsigned int recv(unsigned int dev, unsigned char * data, unsigned int size)
{
    if(dev < dev_size) {
        if(data && size) {
           *data = getchar(dev);
           return 1;
       }
    }
    return 0;
}

static unsigned int send_recv(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if(dev < dev_size) {
        send(send_data, send_size);
        return recv(recv_data, recv_size);
    }
    return 0;
}
static const struct bus bus = {"gpio", {NULL, NULL, getchar}, {send, recv, send_recv}};
const struct bus * const gpio = &bus;
