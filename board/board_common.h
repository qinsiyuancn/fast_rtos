/*
 * common_board.h
 * create by qinsiyuan
 *		on 2016-6-29
 * Ĭ�ϰ忨����
 * ��ֹ����忨���Զ�����©
 * ͨ����������������һ������
 */

 #ifndef __COMMON_BOARD_H__
 #define __COMMON_BOARD_H__
	
	/*
	 * ����cpu�ͺ�
	 */
	#ifndef CPU
	 	#define CPU 
		#define CPU_lpc17xx	1
	 	#include "LPC17xx.h"
	#endif

	/*
	 * �汾�ţ�Ĭ��ѡ�ͨ���������
	 */
	#ifndef VERSION_DATE
		#define VERSION_DATE "2016-7-12"
	#endif

	/*
	 * �忨�ͺţ�Ĭ��ѡ�ͨ���������
	 */
	#ifndef BOARD_NAME
		#define BOARD_NAME "commen"
	#endif

	/*
	 * �Ӱ汾�ţ��忨���ƺ��������
	 */
	#ifndef SUB_VERSION
		#define SUB_VERSION BOARD_NAME "_v" VERSION_DATE
	#endif

	/*
	 * �¶ȹ���ʹ��
	 */
	#if	TEMPERATURE_ENABLE

		/*
		 * �������ڼ��ͺ�
		 * ���ݴ������ͺŲ�ͬ�����벻ͬ����
		 */
		#ifndef TEMPERATURE_DEVICE_DEFINED
			#define TEMPERATURE_DEVICE_DEFINED 
			#ifndef DEVICE_TMC435
				#define DEVICE_TMC435 1
			#endif
		#endif

		/*
		 * �¶Ȼ�ȡ��ʽ
		 */
		#ifndef	TEMPERATURE_I2C_MATHOD
			#define TEMPERATURE_I2C_MATHOD TEMPERATURE_I2C_MATHOD_CHANNEL
		#endif

		#if TEMPERATURE_I2C_MATHOD	//��ͨ����ʽ
			
			/*
			 * ͨ���л�����
			 */
			#ifndef	TEMPERATURE_CHANNEL
				#define TEMPERATURE_CHANNEL	{1,4}
			#endif
			
			/*
			 * ��������������
			 */
			#ifndef BOARD_TEMPERATURE
				
				/*
				 * ���߱��
				 */
				#ifndef BOARD_TEMPERATURE_FD
					#define BOARD_TEMPERATURE_FD 0
				#endif
				
				/*
				 * ���ߴӵ�ַ
				 */
				#ifndef	I2C_TEMPERATURE_SENSOR_ADDR
					#define I2C_TEMPERATURE_SENSOR_ADDR	0x4c
				#endif

	       		#define BOARD_TEMPERATURE {{BOARD_TEMPERATURE_FD, I2C_TEMPERATURE_SENSOR_ADDR}}
			#endif

			/*
			 * ͨ���л���������������
			 */
			#ifndef BOARD_TEMPERATURE_SELECTER
				#define BOARD_TEMPERATURE_SELECTER {0,0x74}
			#endif 
		#else
			
			/*
			 * ��������������
			 */
			#ifndef BOARD_TEMPERATURE

				/*
				 * �������������
				 */
				#ifndef I2C_CARRY_TMP435_FD_U18
					#define I2C_CARRY_TMP435_FD 0
				#endif

				/*
				 * ���������ߴӵ�ַ
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U18
					#define I2C_CARRY_TMP435_ADDR_U18  0x98			// ����p2020�¶�
				#endif
	
				/*
				 * �������������
				 */
				#ifndef I2C_CARRY_TMP435_FD_U32
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * ���������ߴӵ�ַ
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U32
					#define I2C_CARRY_TMP435_ADDR_U32  0x9C			// ����CNP2оƬ�¶�
				#endif

				/*
				 * �������������
				 */
				#ifndef I2C_CARRY_TMP435_FD_U45
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * ���������ߴӵ�ַ
				 */
				#ifndef I2C_CARRY_TMP435_ADDR_U45			
					#define I2C_CARRY_TMP435_ADDR_U45  0x9A			// ����CNP1оƬ�¶�
				#endif
	
				/*
				 * �������������
				 */
				#ifndef I2C_CARRY_TMP435_FD_U37
					#define I2C_CARRY_TMP435_FD I2C_CARRY_TMP435_FD_U18
				#endif

				/*
				 * ���������ߴӵ�ַ
				 */
				#ifndef	I2C_CARRY_TMP435_ADDR_U37
					#define I2C_CARRY_TMP435_ADDR_U37  0x9e			// ����bcm56842оƬ�¶�
				#endif

				#define BOARD_TEMEPRATURE {{I2C_CARRY_TMP435_FD_U18, I2C_CARRY_TMP435_ADDR_U18}, {I2C_CARRY_TMP435_FD_U32, I2C_CARRY_TMP435_ADDR_U32}, {I2C_CARRY_TMP435_FD_U45, I2C_CARRY_TMP435_ADDR_U45}, {I2C_CARRY_TMP435_FD_U37, I2C_CARRY_TMP435_ADDR_U37}}
			#endif
		#endif
	#endif

	/*
	 * ���ȿ���ʹ��
	 */
	#if SHELF_ENABLE
		
		/*
		 * ������������
		 */
		#ifndef BOARD_SHELF

			/*
			 * ����1��������
			 */
			#ifndef SHELF_FAN_1
				
				/*
				 * �����������
				 */
				#ifndef SHELF_FAN_I2C_FD_1
					#define SHELF_FAN_I2C_FD_1 1
				#endif
	
				/*
				 * �������ߴӵ�ַ
				 */
				#ifndef SHELF_FAN_I2C_ADDRESS_1
					#define SHELF_FAN_I2C_ADDRESS_1 0x20
				#endif
				#define SHELF_FAN_1 {SHELF_FAN_I2C_FD_1, SHELF_FAN_I2C_ADDRESS_1}
			#endif

			/*
			 * ����2��������
			 */
			#ifndef SHELF_FAN_2

				/*
				 * �������
				 */
				#ifndef SHELF_FAN_I2C_FD_2
					#define SHELF_FAN_I2C_FD_2 2
				#endif
	
				/*
				 * ���ߴӵ�ַ
				 */
				#ifndef SHELF_FAN_I2C_ADDRESS_2
					#define SHELF_FAN_I2C_ADDRESS_2  0x21
				#endif
				#define SHELF_FAN_2 {SHELF_FAN_I2C_FD_2, SHELF_FAN_I2C_ADDRESS_2}
			#endif

			#define BOARD_SHELF	{SHELF_FAN_1, SHELF_FAN_2}
		#endif

		/*
		 * ��λ����������
		 */
		#ifndef BOARD_SLOT
			
			/*
			 * ��λ��ȡ��gpio����
			 */
			#ifndef	BOARD_SLOT_DATA

				/*
				 * �˿�
				 */
				#ifndef	BOARD_SLOT_PORT
					#define	BOARD_SLOT_PORT	0
				#endif
		
				/*
				 * ƫ��
				 */
				#ifndef	BOARD_SLOT_POS
					#define	BOARD_SLOT_POS 15
				#endif
		
				/*
				 * ����
				 */
				#ifndef	BOARD_SLOT_MASK
					#define	BOARD_SLOT_MASK	0xff
				#endif
			
				#define BOARD_SLOT_DATA {BOARD_SLOT_PORT, BOARD_SLOT_POS, BOARD_SLOT_MASK}
			#endif
	
			/*
			 * slotʹ�ܿ���
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

	 //gpio��������
	 //led����{{��}��{��}��{��}}
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

	// cpld���ж�RTM�Ƿ���λ������
	#ifndef	CPLD_PS
		#define CPLD_PS		{2, 7}
	#endif

	//��Դʹ��
	#ifndef SYS_DC_12V_EN
		#define SYS_DC_12V_EN  {1, 20}
	#endif
	
	/*
	 * ��֧��
	 */
	#if RTM_SUPPORT
	 
		/*
		 * �ж�RTM���Ƿ���λ������
		 */
		#ifndef RTM_PS
			#define RTM_PS		{1, 15}
		#endif

		/*
		 * ��ͨѶ
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
	 * ���ƴӿ����µ�
	 */
	#if REMOTE_BOARD_ENABLE

		#ifndef REMOTE_I2C_FD
			#define REMOTE_I2C_FD 2
		#endif

	#endif

	/*
	 * eeprom��������
	 */
	#ifndef BOARD_EEPROM
		
		/*
		 * �������
		 */
		#ifndef BOARD_EEPROM_I2CFD
			#define BOARD_EEPROM_I2CFD 0
		#endif
		
		/*
		 * ���ߴӵ�ַ
		 */
		#ifndef BOARD_EEPROM_I2CSLAVE
			#define BOARD_EEPROM_I2CSLAVE 0x50
		#endif
		 
		#define BOARD_EEPROM {BOARD_EEPROM_I2CFD, BOARD_EEPROM_I2CSLAVE}
	#endif

 #endif
