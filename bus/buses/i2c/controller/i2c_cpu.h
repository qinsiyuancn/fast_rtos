/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 *     on 2016-6-2
 * i2c与cpu相关驱动部分
 */

#if CPU_lpc17xx

extern unsigned int cpu_i2c_stop(unsigned char fd);

extern unsigned int cpu_i2c_clear_sic(unsigned char fd);

extern unsigned int cpu_i2c_start(unsigned char fd);

extern void I2C_IRQHandler(unsigned char fd);

extern unsigned int cpu_i2c_init(unsigned char fd, enum i2c_mode mode);

#endif

