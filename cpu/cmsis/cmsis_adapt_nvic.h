#ifndef __CMSIS_ADAPT_NVIC_H__
#define __CMSIS_ADAPT_NVIC_H__

extern void init_nvic(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);

#endif
