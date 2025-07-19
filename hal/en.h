/*
 * service_en.h
 * create by qinsiyuan
 *			on 2016-7-25
 * �ṩ��Դʹ�ܷ���
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
	 * ����ʹ�ܲ���
	 * @param �豸����
	 * @param ʹ�ܲ���
	 */
	void set_en(const char *, unsigned char );
	
	/*
	 * ����ȫ��12V�ϵ�
	 * @param ʹ�ܲ���
	 */
	void set_sys_dc_12v_en(unsigned char );

	/*
	 * ����ȫ��12V�ϵ�
	 */
	void set_sys_dc_12v_en_on(void);

	/*
	 * ����ȫ��12V�µ�
	 */
	void set_sys_dc_12v_en_off(void);
	
	/*
	 * ���ú�3V�ϵ����
	 * @param �ϵ�ʹ�ܲ���
	 */
	void set_sys_nrtmen_3_en(unsigned char );

	/*
	 * ���ú�3V�ϵ�
	 */
	void set_sys_nrtmen_3_en_on(void);

	/*
	 * ���ú�3V�µ�
	 */
	void set_sys_nrtmen_3_en_off(void);

	/*
	 * ���ú�12V�ϵ����
	 * @param ���ϵ����
	 */
	void set_sys_nrtmen_12_en(unsigned char sys_nrtmen_12_en_switch);

	 /*
	  *	��12V�ϵ�ʹ��
	  */
	void set_sys_nrtmen_12_en_on(void);

	/*
	 *	�رպ�12V�ϵ�ʹ��
	 */
	void set_sys_nrtmen_12_en_off(void);


	void set_sys_oren(unsigned char sys_nrtmen_12_en_switch);
	void set_sys_oren_on(void);
	void set_sys_oren_off(void);

 
 #endif
