#ifndef __GPIO_H 
#define __GPIO_H

	#include "gpio_lpc17xx.h"

	 /*
	  *	设置gpio高电平
	  * @param 端口
	  * @param 掩码
	  */
	void set_gpio_on(unsigned char port, unsigned int mask);

	 /*
	  *	设置gpio低电平
	  * @param 端口
	  * @param 掩码
	  */
	void set_gpio_off(unsigned char port, unsigned int mask);

	 /*
	  *	获取gpio电平情况
	  * @param 端口
	  * @param 掩码
	  * @return gpio状态
	  */
	unsigned int get_gpio(unsigned char port, unsigned int mask);

	/*
	 * 获取gpio情况
	 * @param 端口
	 * @param 掩码
	 * @param 偏移
	 */	
	unsigned int get_gpio_bits(unsigned char port, unsigned int mask, unsigned char pos);

	/*
 	 *设置gpio单个bit低电平
	 * @param 端口
	 * @param 偏移
	 */			
	void set_gpio_bit_off(unsigned char port, unsigned int bit);

	/*
	 * 设置gpio单个bit高电平
	 * @param 端口
	 * @param 偏移
	 */
	void set_gpio_bit_on(unsigned char port, unsigned int bit);

	/*
	 * 获取gpio单个bit电平情况
	 * @param 端口
	 * @param 偏移
	 * @return 电平情况
	 */
	unsigned char get_gpio_bit(char port, unsigned int bit);

	/*
	 * 初始化gpio
	 */
	void gpio_init(void);

#endif
