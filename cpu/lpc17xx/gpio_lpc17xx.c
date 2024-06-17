/*
 * gpio_lpc17xx.c
 * create by qinsiyuan
 *			on 2016-7-8
 */
#include "gpio_lpc17xx.h"

#if CPU_lpc17xx
static LPC_GPIO_TypeDef * gpio_s [] = GPIO_PORT_LIST;

void set_gpio_on(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            gpio_s[port]->FIODIR |= mask;
            gpio_s[port]->FIOSET |= mask;
        }
    }
}

void set_gpio_off(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            gpio_s[port]->FIODIR |= mask;
            gpio_s[port]->FIOCLR |= mask;
        }
    }
}

unsigned int get_gpio(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            gpio_s[port]->FIODIR &= ~mask;
            return gpio_s[port]->FIOPIN & mask;
        }
    }
    return 0;
}

void gpio_IRQHandler()
{
}

void GpioIntInit(void)
{
    NVIC_EnableIRQ(EINT3_IRQn);
}

#endif
