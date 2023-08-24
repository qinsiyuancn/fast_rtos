#ifndef __GPIO_H 
#define __GPIO_H

	#include "gpio_lpc17xx.h"

	 /*
	  *	����gpio�ߵ�ƽ
	  * @param �˿�
	  * @param ����
	  */
	void set_gpio_on(unsigned char port, unsigned int mask);

	 /*
	  *	����gpio�͵�ƽ
	  * @param �˿�
	  * @param ����
	  */
	void set_gpio_off(unsigned char port, unsigned int mask);

	 /*
	  *	��ȡgpio��ƽ���
	  * @param �˿�
	  * @param ����
	  * @return gpio״̬
	  */
	unsigned int get_gpio(unsigned char port, unsigned int mask);

	/*
	 * ��ȡgpio���
	 * @param �˿�
	 * @param ����
	 * @param ƫ��
	 */	
	unsigned int get_gpio_bits(unsigned char port, unsigned int mask, unsigned char pos);

	/*
 	 *����gpio����bit�͵�ƽ
	 * @param �˿�
	 * @param ƫ��
	 */			
	void set_gpio_bit_off(unsigned char port, unsigned int bit);

	/*
	 * ����gpio����bit�ߵ�ƽ
	 * @param �˿�
	 * @param ƫ��
	 */
	void set_gpio_bit_on(unsigned char port, unsigned int bit);

	/*
	 * ��ȡgpio����bit��ƽ���
	 * @param �˿�
	 * @param ƫ��
	 * @return ��ƽ���
	 */
	unsigned char get_gpio_bit(char port, unsigned int bit);

	/*
	 * ��ʼ��gpio
	 */
	void gpio_init(void);

#endif
