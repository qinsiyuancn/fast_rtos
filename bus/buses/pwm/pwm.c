
static struct gpio_device device_list[] = GPIO_DEV_LIST;

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    static void (* const set_gpio_operation)[](unsigned char port, unsigned int mask) = {
       set_gpio_off,
       set_gpio_on,
    };
    if(dev < dev_size)
        if(data && size > 1) {
            if(data[0] < (sizeof(set_gpio_operation)/sizeof(set_gpio_operation[0])))
                return set_gpio_operation[data[0]](device_list[dev].port, 0x1 << device_list[dev].offset, data[1]);
    return 0;
}


static const struct bus bus = {"pwm", {NULL}, {send}};
bus_pointer pwm = &bus;
