/*
 * gpio.c
 * create by qinsiyuan
 *			on 2016-7-8
 *	gpio总线硬件无关驱动
 */
 #include "gpio.h"

 /*
  *	设置gpio高电平
  * @param 端口
  * @param 掩码
  */
void set_gpio_on(unsigned char port, unsigned int mask)
{
	gpio_manager.set_on(port, mask);
}

 /*
  *	设置gpio低电平
  * @param 端口
  * @param 掩码
  */
void set_gpio_off(unsigned char port, unsigned int mask)
{
	gpio_manager.set_off(port, mask);
}

 /*
  *	获取gpio电平情况
  * @param 端口
  * @param 掩码
  * @return gpio状态
  */
unsigned int get_gpio(unsigned char port, unsigned int mask)
{
	return gpio_manager.get_value(port, mask);
}

/*
 * 获取gpio情况
 * @param 端口
 * @param 掩码
 * @param 偏移
 */
unsigned int get_gpio_bits(unsigned char port, unsigned int mask, unsigned char pos)
{
	return get_gpio(port, mask << pos) >> pos;
}

/*
 * 设置gpio单个bit低电平
 * @param 端口
 * @param 偏移
 */
void set_gpio_bit_off(unsigned char port, unsigned int bit)
{
	set_gpio_off(port, 1 << bit);
}

/*
 * 设置gpio单个bit高电平
 * @param 端口
 * @param 偏移
 */
void set_gpio_bit_on(unsigned char port, unsigned int bit)
{
	set_gpio_on(port, 1 << bit);
}

/*
 * 获取gpio单个bit电平情况
 * @param 端口
 * @param 偏移
 * @return 电平情况
 */
unsigned char get_gpio_bit(char port, unsigned int bit)
{
	return (unsigned char)get_gpio_bits (port, 1 , bit);	
}

/*
 * 初始化gpio
 */
void gpio_init()
{
	gpio_manager.bus_init();
}

