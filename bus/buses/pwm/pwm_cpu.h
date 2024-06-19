/*
 * pwm.h
 * create by qinsiyuan
 *			on 2024-6-17
 */

#ifndef __PWM_H__
#define __PWM_H__

extern void pwm_cfg(unsigned int dev, uint32_t OCMode, uint32_t percent, uint32_t OCPolarity, uint32_t OCNPolarity, uint32_t OCFastMode, uint32_t OCIdleState, uint32_t OCNIdleState);

extern void pwm_cfg_percent(unsigned int dev, unsigned char percent);

extern void pwm_cfg_default(unsigned int dev, unsigned int config);

extern unsigned int pwm_run(unsigned int dev);

extern void pwm_init();

#endif
