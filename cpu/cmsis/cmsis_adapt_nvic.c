#include "cmsis_adapt_nvic.h"

void init_nvic(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    HAL_NVIC_SetPriority(EXTI1_IRQn, PreemptPriority, SubPriority);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}
