/*
 * service_board.h
 * 与同一机架的其他卡通讯
 */
 #ifndef __SERVICE_BOARD_H__
 #define __SERVICE_BOARD_H__

	#include "file_service.h"

	#if	REMOTE_BOARD_ENABLE	

		#define I2C_CMD_POWEROFF			1
		#define I2C_CMD_POWERON				2
		#define I2C_CMD_READ_TEMPERATURE	3

		#ifndef SERVICE_BOARD_POWER_ON
			#define	SERVICE_BOARD_POWER_ON service_board_power_on,
		#endif
		#ifndef SERVICE_BOARD_POWER_OFF
			#define	SERVICE_BOARD_POWER_OFF service_board_power_off,
		#endif
		
		int board_operation(unsigned char slot, unsigned char operation);
		int board_power_on(unsigned char slot);
		int board_power_off(unsigned char slot);
	
		int service_board_power_on(char *msg);
		int service_board_power_off(char *msg);

	#endif	
	
	#ifndef SERVICE_BOARD_POWER_ON						 
		#define SERVICE_BOARD_POWER_ON
	#endif
	#ifndef	SERVICE_BOARD_POWER_OFF				 
		#define SERVICE_BOARD_POWER_OFF
	#endif

 #endif

