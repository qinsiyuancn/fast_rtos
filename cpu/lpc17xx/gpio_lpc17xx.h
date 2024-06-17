#ifndef __GPIO_LPC17XX_H__ 
#define __GPIO_LPC17XX_H__

#include "board_manager.h"
	#if CPU_lpc17xx
		#include "gpio_bus.h"
		
			/*
			 * GPIO地址
			 */ 
		 	#define GPIO_A {\
				LPC_GPIO0,	\
				LPC_GPIO1,	\
				LPC_GPIO2,	\
				LPC_GPIO3	\
			}
			SET_GPIO_MANAGEER();
	#endif
#endif

