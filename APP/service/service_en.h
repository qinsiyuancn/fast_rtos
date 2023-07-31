/*
 * service_en.h
 * create by qinsiyuan
 *			on 2016-7-25
 * 提供电源使能服务
 */

 #ifndef __SERVICE_EN_H__
 #define __SERVICE_EN_H__

	#include "file_service.h"
	
	#ifndef en_on
		#define en_on 0
	#endif

	#ifndef en_off
		#define en_off 1
	#endif

	#ifndef sys_dc_12v_en_on
		#define sys_dc_12v_en_on 		en_on
	#endif

	#ifndef sys_dc_12v_en_off
		#define sys_dc_12v_en_off		en_off
	#endif

	#ifndef sys_nrtmen_3_en_on
		#define sys_nrtmen_3_en_on 		en_on
	#endif

	#ifndef sys_nrtmen_3_en_off
		#define sys_nrtmen_3_en_off		en_off
	#endif

	#ifndef sys_nrtmen_12_en_on
		#define sys_nrtmen_12_en_on 	en_on
	#endif

	#ifndef sys_nrtmen_12_en_off
		#define sys_nrtmen_12_en_off	en_off
	#endif

	#ifndef sys_oren_on
		#define sys_oren_on 			en_on
	#endif

	#ifndef sys_oren_off
		#define sys_oren_off			en_off
	#endif

	/*
	 * 设置使能操作
	 * @param 设备名称
	 * @param 使能操作
	 */
	void set_en(const char *, unsigned char );
	
	/*
	 * 设置全局12V上电
	 * @param 使能操作
	 */
	void set_sys_dc_12v_en(unsigned char );

	/*
	 * 设置全局12V上电
	 */
	void set_sys_dc_12v_en_on(void);

	/*
	 * 设置全局12V下电
	 */
	void set_sys_dc_12v_en_off(void);
	
	/*
	 * 设置后卡3V上电操作
	 * @param 上电使能操作
	 */
	void set_sys_nrtmen_3_en(unsigned char );

	/*
	 * 设置后卡3V上电
	 */
	void set_sys_nrtmen_3_en_on(void);

	/*
	 * 设置后卡3V下电
	 */
	void set_sys_nrtmen_3_en_off(void);

	/*
	 * 设置后卡12V上电操作
	 * @param 后卡上电操作
	 */
	void set_sys_nrtmen_12_en(unsigned char sys_nrtmen_12_en_switch);

	 /*
	  *	后卡12V上电使能
	  */
	void set_sys_nrtmen_12_en_on(void);

	/*
	 *	关闭后卡12V上电使能
	 */
	void set_sys_nrtmen_12_en_off(void);


	void set_sys_oren(unsigned char sys_nrtmen_12_en_switch);
	void set_sys_oren_on(void);
	void set_sys_oren_off(void);

 
 #endif
