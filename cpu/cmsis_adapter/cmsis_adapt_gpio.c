/*
 * cmsis_adapt_gpio.c
 * create by qinsiyuan
 *			on 2024-6-17
 */

#include "cmsis_adapt_clk.h"
#include "cmsis_adapt_nvic.h"
#include "stm32f4xx_hal_gpio.h"

static GPIO_TypeDef * const gpio_s [] = GPIO_PORT_LIST;

void set_gpio_on(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            HAL_GPIO_WritePin(gpio_s[port], mask, GPIO_PIN_SET);
        }
    }
}

void set_gpio_off(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            HAL_GPIO_WritePin(gpio_s[port], mask, GPIO_PIN_RESET);
        }
    }
}

unsigned int get_gpio(unsigned char port, unsigned int mask)
{
    if(port < sizeof(gpio_s)/sizeof(gpio_s[0])){
        if(gpio_s[port]){
            return HAL_GPIO_ReadPin(gpio_s[port], mask);
        }
    }
    return -1u;
}

void gpio_IRQHandler()
{
    //判断发生中断的引脚，调用回调函数
}

static void init_gpio_clk()
{
    unsigned long i = 0;
    while(i < CMSIS_GPIO_PORT_COUNT)
       cmsis_adapt_init_clk_pos(i);
}

static void init_pin()
{
    static const struct {
        const GPIO_InitTypeDef init;
        GPIO_TypeDef* const port;
    } list [] = GPIO_INIT_LIST;
    unsigned int i = 0;
    while(i < (sizeof(list) / sizeof(list[1])))
        HAL_GPIO_Init(list[i].port, &list[i++].init)
}

static void init_irq()
{
    static const struct {
        IRQn_Type IRQn;
       	uint32_t PreemptPriority;
       	uint32_t SubPriority;
    } list[] = GPIO_IRQ_LIST;
    unsigned int i = 0;
    while(i < (sizeof(list)/sizeof(list[0])))
        init_nvic(list[i].IRQn, list[i].PreemptPriority, list[i++].SubPriority);
}

void GpioIntInit(void)
{
    void (static *const init_list[])() = {init_gpio_clk, init_pin, init_irq};
    unsigned int i = 0;
    while(i < (sizeof(init_list)/sizeof(init_list[0])))
        init_list[i++]();
    NVIC_EnableIRQ(EINT3_IRQn);  	
}

