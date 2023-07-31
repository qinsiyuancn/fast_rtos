/*
 * gpio_bus.h
 * create by qinsiyuan
 * 			on 2016-7-8
 * gpio具体总线驱动暴露给抽象驱动的接口
 */
 #ifndef __GPIO_BUS_H__
 #define __GPIO_BUS_H__
  struct gpio_manager_s{
	void (*bus_init)(void);
	unsigned int (*get_value)(unsigned char , unsigned int);
	void (*set_off)(unsigned char , unsigned int );
	void (*set_on)(unsigned char , unsigned int );
	void (*IRQHandler)();
 };
 #define SET_GPIO_MANAGEER() extern const struct gpio_manager_s gpio_manager

 #endif
