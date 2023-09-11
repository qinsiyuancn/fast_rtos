/*
 * gpio_lpc17xx.c
 * create by qinsiyuan
 *			on 2016-7-8
 * 与lpc17xx芯片相关驱动
 */
#include "gpio_lpc17xx.h"

#if CPU_lpc17xx
static LPC_GPIO_TypeDef * gpio_s [] = GPIO_A;

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
    //判断发生中断的引脚，调用回调函数
}

void GpioIntInit(void)
{
//  LPC_GPIO0->FIODIR &= ~(0x1 << 29);	   // gpio方向为输入
//  LPC_GPIOINT->IO0IntEnF |= 0x1 << 29;   // 下降沿使能	
    NVIC_EnableIRQ(EINT3_IRQn);  	
}

// const struct gpio_manager_s gpio_manager = {GpioIntInit, get_gpio, set_gpio_off, set_gpio_on, gpio_IRQHandler};
#endif
