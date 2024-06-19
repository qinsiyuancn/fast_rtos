/*
 * cmsis_adapt_pwm.c
 * create by qinsiyuan
 *			on 2024-6-17
 */

#include "stm32f4xx_hal_tim.h"

#define GET_AIR_PWM_PERIOD(cnt_clk, pwm_freq)           ((cnt_clk) / (pwm_freq) - 1)

static const struct {
    TIM_HandleTypeDef *const htim;
    uint32_t channel;
} list[] = CMSIS_PWM_LIST;

void pwm_cfg(unsigned int dev, uint32_t OCMode, uint32_t percent, uint32_t OCPolarity, uint32_t OCNPolarity, uint32_t OCFastMode, uint32_t OCIdleState, uint32_t OCNIdleState)
{
    TIM_OC_InitTypeDef sConfigOC[1] = {
            {
               OCMode, (GET_AIR_PWM_PERIOD(VALUE_STEAM_TIM_CNT_CLK, VALUE_STEAM_PWM_FREQ) * percent / 100,
               OCPolarity, OCNPolarity, OCFastMode, OCIdleState, OCNIdleState
            },
    };
    HAL_TIM_PWM_ConfigChannel(list[dev].htim, sConfig, list[dev].channel);
}

void pwm_cfg_percent(unsigned int dev, unsigned char percent)
{
    TIM_OC_InitTypeDef sConfigOC[1] = TIM_OC_InitTypeDef sConfigOC[1] = {
        {
            TIM_OCMODE_PWM1, (GET_AIR_PWM_PERIOD(VALUE_STEAM_TIM_CNT_CLK, VALUE_STEAM_PWM_FREQ) * percent / 100, TIM_OCPOLARITY_HIGH,
            0, TIM_OCFAST_DISABLE
        }
    };
    if(dev < sizeof(list)/sizeof(list[0]))
        HAL_TIM_PWM_ConfigChannel(list[dev].htim, sConfig, list[dev].channel);
}

void pwm_cfg_default(unsigned int dev, unsigned int config)
{
    static const TIM_OC_InitTypeDef sConfigOC[] = CMSIS_ADAPT_PWM_CONFIG;

    if(dev < sizeof(list)/sizeof(list[0]))
        if(config < sizeof(sConfigOC)/sizeof(sConfigOC[0]))
            HAL_TIM_PWM_ConfigChannel(list[dev].htim, sConfig, list[dev].channel);
}

unsigned int pwm_run(unsigned int dev)
{
    if(dev < (sizeof(list)/sizeof(list[0]))){
    /* Enable the Capture compare channel */
        TIM_CCxChannelCmd(list[dev].htim->Instance, list[dev].channel, TIM_CCx_ENABLE);
	return 1;
    }
    return 0;
}

void pwm_init()
{
    unsigned int i = 0;
    while(i < (sizeof(list)/sizeof(list[0])))
        HAL_TIM_PWM_Start(list[i].htim, list[i++].channel);
}
#endif
