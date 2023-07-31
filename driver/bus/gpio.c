/*
 * gpio.c
 * create by qinsiyuan
 *			on 2016-7-8
 *	gpio����Ӳ���޹�����
 */
 #include "gpio.h"

 /*
  *	����gpio�ߵ�ƽ
  * @param �˿�
  * @param ����
  */
void set_gpio_on(unsigned char port, unsigned int mask)
{
	gpio_manager.set_on(port, mask);
}

 /*
  *	����gpio�͵�ƽ
  * @param �˿�
  * @param ����
  */
void set_gpio_off(unsigned char port, unsigned int mask)
{
	gpio_manager.set_off(port, mask);
}

 /*
  *	��ȡgpio��ƽ���
  * @param �˿�
  * @param ����
  * @return gpio״̬
  */
unsigned int get_gpio(unsigned char port, unsigned int mask)
{
	return gpio_manager.get_value(port, mask);
}

/*
 * ��ȡgpio���
 * @param �˿�
 * @param ����
 * @param ƫ��
 */
unsigned int get_gpio_bits(unsigned char port, unsigned int mask, unsigned char pos)
{
	return get_gpio(port, mask << pos) >> pos;
}

/*
 * ����gpio����bit�͵�ƽ
 * @param �˿�
 * @param ƫ��
 */
void set_gpio_bit_off(unsigned char port, unsigned int bit)
{
	set_gpio_off(port, 1 << bit);
}

/*
 * ����gpio����bit�ߵ�ƽ
 * @param �˿�
 * @param ƫ��
 */
void set_gpio_bit_on(unsigned char port, unsigned int bit)
{
	set_gpio_on(port, 1 << bit);
}

/*
 * ��ȡgpio����bit��ƽ���
 * @param �˿�
 * @param ƫ��
 * @return ��ƽ���
 */
unsigned char get_gpio_bit(char port, unsigned int bit)
{
	return (unsigned char)get_gpio_bits (port, 1 , bit);	
}

/*
 * ��ʼ��gpio
 */
void gpio_init()
{
	gpio_manager.bus_init();
}

