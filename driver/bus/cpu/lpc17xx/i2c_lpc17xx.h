/*
 * i2c_lpc17xx.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c与cpu相关部分驱动
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
		 * I2C总线结构体描述
		 * {地址，电源(设置寄存器PCONP)，{引脚功能选择}}
		 */
		 #define I2C_A {\
						{LPC_I2C0, 7, {&(LPC_PINCON->PINSEL1),0x01400000}},\
					 	{LPC_I2C1, 19, {&(LPC_PINCON->PINSEL0), 0xf}},\
					  	{LPC_I2C2, 26, {&(LPC_PINCON->PINSEL0), 0xaa << 20}}\
					}
		#if 0
		/*
		 * I2C回调函数列表
		 * 写成两部分是为了方便剪裁 
		 */
		 #define I2C_CALLBACK_COLLECT_MASTER 													\
		/*0x00	由于非法起始或停止条件的出现，在MST或选择的从机模式中将出现总线错误。			 \
		当外部干扰使I2C 模块进入未定义的状态时也出现0x00状态*/							NULL, 	  \
		/*0x08	已发送起始条件*/														set_addr,  \
		/*0x10	已发送重复的起始条件*/													set_addr, 	\
		/*0x18	已发送SLA+W，已接收ACK*/												sended_ack,  \
		/*0x20	已发送SLA+W，已接收非ACK*/												sended_ack,\//sended_nack,  \
		/*0x28	已发送I2DAT中的数据字节，已接收ACK*/									sended_ack,	   \
		/*0x30	已发送I2DAT中的数据字节，已接收非ACK*/									sended_ack,\//sended_nack,	\
		/*0x38	在SLA+R/W或数据字节中丢失仲裁，在非ACK位中丢失仲裁*/					clear_sic,		 \
		/*0x40	已发送SLA+R，已接收ACK*/												set_ack,		  \
		/*0x48	已发送SLA+R，已接收非ACK*/												clear_sic,		   \
		/*0x50	已接收数据字节，ACK已返回*/												recv,				\
		/*0x58	已接收数据字节，非ACK已返回*/											recv,				 
		
		#define I2C_CALLBACK_COLLECT_SLAVE 													   \
		/*0x68	主控器时在SLA+R/W中丢失仲裁；已接收自身SLA+W，已返回ACK*/						\
		/*0x70	已接收通用调用地址（0x00）；已返回ACK*/											 \
		/*0x78	主控器在SLA+R/W中丢失仲裁；已接收通用调用地址，已应答*/							  \
		/*0x08	前一次寻址使用自身从地址；已接收数据字节；已返回ACK*/							   \
		/*0x88	前一次寻址使用自身SLA；已接收数据字节；已返回非ACK*/								\
		/*0x90	前一次寻址使用通用调用；已接收数据字节；已返回ACK*/									 \
		/*0x98	前一次寻址使用通用调用；已接收数据字节；已返回非ACK*/								  \
		/*0xA0	当使用SLV/REC或SLV/TRX 静态寻址时，接收到停止条件或重复的起始条件*/					   \
		/*0xA8	已接收自身的SLA+R； 已返回ACK*/															\
		/*0xB0	主控器时在SLA+R/W 中丢失仲裁；已返回ACK*/												 \
		/*0xB8	已接收I2DAT中的数据字节；已返回ACK*/													  \
		/*0xC0	已接收I2DAT中的数据字节；已返回非ACK*/													   \
		/*0xC8	最后一个I2DAT中的数据字节已被发送（AA=0）；已接收ACK*/										
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
