#include "cmsis_adapt_clk.h"

#define HAL_CLK_ENABLE(RCC_AHB1ENR_EN) do { \
                                                     __IO uint32_t tmpreg = 0x00U; \
                                                     SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_EN);\
                                                     /* Delay after an RCC peripheral clock enabling */ \
                                                     tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_EN);\
                                                     UNUSED(tmpreg); \
                                                     } while(0U)

void cmsis_adapt_init_clk(unsigned long en)
{
    HAL_CLK_ENABLE(en);
}

void cmsis_adapt_init_clk_pos(unsigned long pos)
{
    cmsis_adapt_init_clk(0x1 << pos);
}
