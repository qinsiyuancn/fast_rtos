/*
 * i2c_lpc17xx.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c��cpu��ز�������
 */
 #ifndef __I2C_LPC1764_H__
 #define __I2C_LPC1764_H__

#include "board_manager.h"
	#if CPU_lpc17xx
		#include "i2c_bus.h"
		
		#define I2CONSET_I2EN		0x00000040  /* I2C Control Set Register */ 
		#define I2CONSET_AA			0x00000004 
		#define I2CONSET_SI			0x00000008 
		#define I2CONSET_STO		0x00000010 
		#define I2CONSET_STA		0x00000020 
		 
		#define I2CONCLR_AAC		0x00000004  /* I2C Control clear Register */ 
		#define I2CONCLR_SIC		0x00000008 
		#define I2CONCLR_STAC		0x00000020 
		#define I2CONCLR_I2ENC		0x00000040 
		 
		#define I2DAT_I2C			0x00000000  /* I2C Data Reg */ 
		#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */ 
		#define I2SCLH_SCLH			0x00000080  /* I2C SCL Duty Cycle High Reg */ 
		#define I2SCLL_SCLL			0x00000080  /* I2C SCL Duty Cycle Low Reg */ 
		/*
		 * I2C���߽ṹ������
		 * {��ַ����Դ(���üĴ���PCONP)��{���Ź���ѡ��}}
		 */
		 #define I2C_A {\
						{LPC_I2C0, 7, {&(LPC_PINCON->PINSEL1),0x01400000}},\
					 	{LPC_I2C1, 19, {&(LPC_PINCON->PINSEL0), 0xf}},\
					  	{LPC_I2C2, 26, {&(LPC_PINCON->PINSEL0), 0xaa << 20}}\
					}
		#if 0
		/*
		 * I2C�ص������б�
		 * д����������Ϊ�˷������ 
		 */
		 #define I2C_CALLBACK_COLLECT_MASTER 													\
		/*0x00	���ڷǷ���ʼ��ֹͣ�����ĳ��֣���MST��ѡ��Ĵӻ�ģʽ�н��������ߴ���			 \
		���ⲿ����ʹI2C ģ�����δ�����״̬ʱҲ����0x00״̬*/							NULL, 	  \
		/*0x08	�ѷ�����ʼ����*/														set_addr,  \
		/*0x10	�ѷ����ظ�����ʼ����*/													set_addr, 	\
		/*0x18	�ѷ���SLA+W���ѽ���ACK*/												sended_ack,  \
		/*0x20	�ѷ���SLA+W���ѽ��շ�ACK*/												sended_ack,\//sended_nack,  \
		/*0x28	�ѷ���I2DAT�е������ֽڣ��ѽ���ACK*/									sended_ack,	   \
		/*0x30	�ѷ���I2DAT�е������ֽڣ��ѽ��շ�ACK*/									sended_ack,\//sended_nack,	\
		/*0x38	��SLA+R/W�������ֽ��ж�ʧ�ٲã��ڷ�ACKλ�ж�ʧ�ٲ�*/					clear_sic,		 \
		/*0x40	�ѷ���SLA+R���ѽ���ACK*/												set_ack,		  \
		/*0x48	�ѷ���SLA+R���ѽ��շ�ACK*/												clear_sic,		   \
		/*0x50	�ѽ��������ֽڣ�ACK�ѷ���*/												recv,				\
		/*0x58	�ѽ��������ֽڣ���ACK�ѷ���*/											recv,				 
		
		#define I2C_CALLBACK_COLLECT_SLAVE 													   \
		/*0x68	������ʱ��SLA+R/W�ж�ʧ�ٲã��ѽ�������SLA+W���ѷ���ACK*/						\
		/*0x70	�ѽ���ͨ�õ��õ�ַ��0x00�����ѷ���ACK*/											 \
		/*0x78	��������SLA+R/W�ж�ʧ�ٲã��ѽ���ͨ�õ��õ�ַ����Ӧ��*/							  \
		/*0x08	ǰһ��Ѱַʹ������ӵ�ַ���ѽ��������ֽڣ��ѷ���ACK*/							   \
		/*0x88	ǰһ��Ѱַʹ������SLA���ѽ��������ֽڣ��ѷ��ط�ACK*/								\
		/*0x90	ǰһ��Ѱַʹ��ͨ�õ��ã��ѽ��������ֽڣ��ѷ���ACK*/									 \
		/*0x98	ǰһ��Ѱַʹ��ͨ�õ��ã��ѽ��������ֽڣ��ѷ��ط�ACK*/								  \
		/*0xA0	��ʹ��SLV/REC��SLV/TRX ��̬Ѱַʱ�����յ�ֹͣ�������ظ�����ʼ����*/					   \
		/*0xA8	�ѽ��������SLA+R�� �ѷ���ACK*/															\
		/*0xB0	������ʱ��SLA+R/W �ж�ʧ�ٲã��ѷ���ACK*/												 \
		/*0xB8	�ѽ���I2DAT�е������ֽڣ��ѷ���ACK*/													  \
		/*0xC0	�ѽ���I2DAT�е������ֽڣ��ѷ��ط�ACK*/													   \
		/*0xC8	���һ��I2DAT�е������ֽ��ѱ����ͣ�AA=0�����ѽ���ACK*/										
		#endif
		
		 struct i2c_s{
			LPC_I2C_TypeDef * const bus;
			const unsigned int pconp;
			const struct{
				volatile uint32_t * const pin_p;
				const unsigned int pin_v;
			} pin;
		};
		#define i2c_count() (sizeof(i2cs)/sizeof(i2cs[0]))
		extern const struct i2c_manager_s * const i2c_bus_manager;
	#endif
#endif
