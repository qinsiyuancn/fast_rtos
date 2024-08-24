
static unsigned int data2uint(const unsigned char *data, unsigned int size)
{

}

#if 0

static unsigned int config_default(unsigned int dev, const unsigned char * data, unsigned int size)
{
    pwm_cfg_default(dev, data2uint(data, size));
    return 0;
}

static unsigned int config_percent(unsigned int dev, const unsigned char * data, unsigned int size)
{
    pwm_cfg_percent(dev, *(data+1));
    return 0;
}

static unsigned int config(unsigned int dev, const unsigned char * data, unsigned int size)
{

}

static unsigned int run(unsigned int dev, const unsigned char *data, unsigned int size)
{
    return pwm_run(dev); 
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    static void (* const set_gpio_operation)[](unsigned int , const unsigned char *, unsigned int) = {
       run,
       config,
       config_percent,
       config_default,
    };

    if(data && size > 1) {
        if(data[0] < (sizeof(set_gpio_operation)/sizeof(set_gpio_operation[0])))
            return set_gpio_operation[data[0]](dev, data, size);

    return 0;
}

#endif

static unsigned int config_percent(unsigned int dev, unsigned char data)
{
    pwm_cfg_percent(dev, data);
    return 0;
}

static unsigned int run(unsigned int dev)
{
    return pwm_run(dev);
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    config_percent(dev,*data);
    return run(dev);
}

static const struct bus bus = {"pwm", {NULL}, {send}};
bus_pointer pwm = &bus;
