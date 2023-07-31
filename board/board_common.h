/*
 * common_board.h
 * create by qinsiyuan
 *		on 2016-6-29
 * 默认板卡属性
 * 防止特殊板卡属性定义遗漏
 * 通常特殊属性优先于一般属性
 */

 #ifndef __COMMON_BOARD_H__
 #define __COMMON_BOARD_H__
	
	/*
	 * 定义cpu型号
	 */
	#ifndef CPU
	 	#define CPU 
		#define CPU_lpc17xx	1
	 	#include "LPC17xx.h"
	#endif

	/*
	 * 版本号，默认选项，通常不会出现
	 */
	#ifndef VERSION_DATE
		#define VERSION_DATE "2016-7-12"
	#endif

	/*
	 * 板卡型号，默认选项，通常不会出现
	 */
	#ifndef BOARD_NAME
		#define BOARD_NAME "commen"
	#endif

	/*
	 * 子版本号，板卡名称和日期组合
	 */
	#ifndef SUB_VERSION
		#define SUB_VERSION BOARD_NAME "_v" VERSION_DATE
	#endif

	/*
	 * 温度功能使能
	 */
	#if	TEMPERATURE_ENABLE

		/*
		 * 传感器期间型号
		 * 根据传感器型号不同，编译不同驱动
		 */
		#ifndef TEMPERATURE_DEVICE_DEFINED
			#define TEMPERATURE_DEVICE_DEFINED 
			#ifndef DEVICE_TMC435
				#define DEVICE_TMC435 1
			#endif
		#endif

		/*
		 * 温度获取方式
		 */
		#ifndef	TEMPERATURE_I2C_MATHOD
			#define TEMPERATURE_I2C_MATHOD TEMPERATURE_I2C_MATHOD_CHANNEL
		#endif

		#if TEMPERATURE_I2C_MATHOD	//切通道方式
			
			/*
			 * 通道切换描述
			 */
			#ifndef	TEMPERATURE_CHANNEL
				#define TEMPERATURE_CHANNEL	{1,4}
			#endif
			
			/*
			 * 传感器总线描述
			 */
			#ifndef BOARD_TEMPERATURE
				
				/*
				 * 总线编号
				 */
				#ifndef BOARD_TEMPERATURE_FD
					#define BOARD_TEMPERATURE_FD 0
				#endif
				
				/*
				 * 总线从地址
				 */
				#ifndef	I2C_TEMPERATURE_SENSOR_ADDR
					#define I2C_TEMPERATURE_SENSOR_ADDR	0x4c
				#endif

	       		#define BOARD_TEMPERATURE {{BOARD_TEMPERATURE_FD, I2C_TEMPERATURE_SENSOR_ADDR}}
			#endif

			/*
			 * 通道切换控制器总线描述
			 */
			#ifndef BOARD_TEMPERATURE_SELECTER
				#define BOARD_TEMPERATURE_SELECTER {0,0x74}
			#endif 
		#else
			
			/*
			 * 传感器总线描述
			 */
			#ifndef BOARD_TEMPERATURE

				/*
				 * 传感器总线序号
				 */
				#ifndef I2C_CARRY_TMP435_FD_U18
					#define I2C_CARRY_TMP435_FD 0
				#endif

				/*
				 * 传感器总线从地址
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U18
					#define I2C_CARRY_TMP435_ADDR_U18  0x98			// 测量p2020温度
				#endif
	
				/*
				 * 传感器总线序号
				 */
				#ifndef I2C_CARRY_TMP435_FD_U32
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * 传感器总线从地址
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U32
					#define I2C_CARRY_TMP435_ADDR_U32  0x9C			// 测量CNP2芯片温度
				#endif

				/*
				 * 传感器总线序号
				 */
				#ifndef I2C_CARRY_TMP435_FD_U45
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * 传感器总线从地址
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U45			
					#define I2C_CARRY_TMP435_ADDR_U45  0x9A			// 测量CNP1芯片温度
				#endif
	
				/*
				 * 传感器总线序号
				 */
				#ifndef I2C_CARRY_TMP435_FD_U37
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * 传感器总线从地址
				 */
				#ifndef	I2C_CARRY_TMP435_ADDR_U37
					#define I2C_CARRY_TMP435_ADDR_U37  0x9e			// 测量bcm56842芯片温度
				#endif

				#define BOARD_TEMEPRATURE {{I2C_CARRY_TMP435_FD_U18, I2C_CARRY_TMP435_ADDR_U18}, {I2C_CARRY_TMP435_FD_U32, I2C_CARRY_TMP435_ADDR_U32}, {I2C_CARRY_TMP435_FD_U45, I2C_CARRY_TMP435_ADDR_U45}, {I2C_CARRY_TMP435_FD_U37, I2C_CARRY_TMP435_ADDR_U37}}
			#endif
		#endif
	#endif

	/*
	 * 风扇控制使能
	 */
	#if SHELF_ENABLE
		
		/*
		 * 风扇总线描述
		 */
		#ifndef BOARD_SHELF

			/*
			 * 风扇1总线描述
			 */
			#ifndef SHELF_FAN_1
				
				/*
				 * 风扇总线序号
				 */
				#ifndef SHELF_FAN_I2C_FD_1
					#define SHELF_FAN_I2C_FD_1 1
				#endif
	
				/*
				 * 风扇总线从地址
				 */
				#ifndef SHELF_FAN_I2C_ADDRESS_1
					#define SHELF_FAN_I2C_ADDRESS_1 0x20
				#endif
				#define SHELF_FAN_1 {SHELF_FAN_I2C_FD_1, SHELF_FAN_I2C_ADDRESS_1}
			#endif

			/*
			 * 风扇2总线描述
			 */
			#ifndef SHELF_FAN_2

				/*
				 * 总线序号
				 */
				#ifndef SHELF_FAN_I2C_FD_2
					#define SHELF_FAN_I2C_FD_2 2
				#endif
	
				/*
				 * 总线从地址
				 */
				#ifndef SHELF_FAN_I2C_ADDRESS_2
					#define SHELF_FAN_I2C_ADDRESS_2  0x21
				#endif
				#define SHELF_FAN_2 {SHELF_FAN_I2C_FD_2, SHELF_FAN_I2C_ADDRESS_2}
			#endif

			#define BOARD_SHELF	{SHELF_FAN_1, SHELF_FAN_2}
		#endif

		/*
		 * 槽位号总线描述
		 */
		#ifndef BOARD_SLOT
			
			/*
			 * 槽位获取的gpio描述
			 */
			#ifndef	BOARD_SLOT_DATA

				/*
				 * 端口
				 */
				#ifndef	BOARD_SLOT_PORT
					#define	BOARD_SLOT_PORT	0
				#endif
		
				/*
				 * 偏移
				 */
				#ifndef	BOARD_SLOT_POS
					#define	BOARD_SLOT_POS 15
				#endif
		
				/*
				 * 掩码
				 */
				#ifndef	BOARD_SLOT_MASK
					#define	BOARD_SLOT_MASK	0xff
				#endif
			
				#define BOARD_SLOT_DATA {BOARD_SLOT_PORT, BOARD_SLOT_POS, BOARD_SLOT_MASK}
			#endif
	
			/*
			 * slot使能开关
			 */
			#ifndef BOARD_SLOT_ENABLE
	
				#ifndef BOARD_SLOT_ENABLE_PORT 
					#define BOARD_SLOT_ENABLE_PORT 0x0
				#endif
					
				#ifndef BOARD_SLOT_ENABLE_POS 
					#define	BOARD_SLOT_ENABLE_POS 0x8
				#endif
	
				#define BOARD_SLOT_ENABLE {BOARD_SLOT_ENABLE_PORT, BOARD_SLOT_ENABLE_POS}
			#endif
			
			#define BOARD_SLOT {BOARD_SLOT_ENABLE, BOARD_SLOT_DATA}
	
		#endif
	#endif

	#ifndef IPMB_BUFFER_EN
		#define IPMB_BUFFER_EN {1, 21}
	#endif

	#ifndef BOARD_TTYS
		#define	BOARD_TTYS 0
	#endif

	 //gpio驱动描述
	 //led描述{{蓝}，{红}，{黄}}
	#ifndef BOARD_GPIO_LED
		#ifndef BOARD_GPIO_LED_BLUE
			#define BOARD_GPIO_LED_BLUE {0,4} 	
		#endif
 
		#ifndef BOARD_GPIO_LED_RED
			#define BOARD_GPIO_LED_RED {0,5} 	
		#endif

		#ifndef BOARD_GPIO_LED_YELLOW
			#define BOARD_GPIO_LED_YELLOW {0,6} 	
		#endif

		#define BOARD_GPIO_LED {BOARD_GPIO_LED_BLUE, BOARD_GPIO_LED_RED, BOARD_GPIO_LED_YELLOW}
	#endif

	 //RTM
	#ifndef SYS_NRTMEN_12
		#define SYS_NRTMEN_12 {1, 0}
	#endif

	#ifndef SYS_NRTMEN_3
		#define SYS_NRTMEN_3  {1, 1}
	#endif

	#ifndef	SYS_OREN
		#define SYS_OREN      {1, 4}
	#endif

	// cpld的判断RTM是否在位的引脚
	#ifndef	CPLD_PS
		#define CPLD_PS		{2, 7}
	#endif

	//电源使能
	#ifndef SYS_DC_12V_EN
		#define SYS_DC_12V_EN  {1, 20}
	#endif
	
	/*
	 * 后卡支持
	 */
	#if RTM_SUPPORT
	 
		/*
		 * 判断RTM卡是否在位的引脚
		 */
		#ifndef RTM_PS
			#define RTM_PS		{1, 15}
		#endif

		/*
		 * 后卡通讯
		 */
		#ifndef BOARD_RTM

			#ifndef BOARD_RTM_I2CFD
				#define BOARD_RTM_I2CFD 0
			#endif
			
			#ifndef BOARD_RTM_I2CSLAVE
				#define BOARD_RTM_I2CSLAVE 0x70
			#endif

			#define BOARD_RTM {BOARD_RTM_I2CFD, BOARD_RTM_I2CSLAVE}
		#endif
	#endif
    
	/*
	 * 控制从卡上下电
	 */
	#if REMOTE_BOARD_ENABLE

		#ifndef REMOTE_I2C_FD
			#define REMOTE_I2C_FD 2
		#endif

	#endif

	/*
	 * eeprom驱动描述
	 */
	#ifndef BOARD_EEPROM
		
		/*
		 * 总线序号
		 */
		#ifndef BOARD_EEPROM_I2CFD
			#define BOARD_EEPROM_I2CFD 0
		#endif
		
		/*
		 * 总线从地址
		 */
		#ifndef BOARD_EEPROM_I2CSLAVE
			#define BOARD_EEPROM_I2CSLAVE 0x50
		#endif
		 
		#define BOARD_EEPROM {BOARD_EEPROM_I2CFD, BOARD_EEPROM_I2CSLAVE}
	#endif

 #endif
