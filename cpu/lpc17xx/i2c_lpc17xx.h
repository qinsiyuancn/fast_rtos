/*
 * i2c_lpc17xx.h
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c与cpu相关部分驱动
 */
 #ifndef __I2C_LPC1764_H__
 #define __I2C_LPC1764_H__

// #include "board_manager.h"
    #if CPU_lpc17xx
 //   #include "i2c_bus.h"

    #define I2CONSET_I2EN    0x00000040  /* I2C Control Set Register */
    #define I2CONSET_AA	     0x00000004
    #define I2CONSET_SI	     0x00000008
    #define I2CONSET_STO     0x00000010
    #define I2CONSET_STA     0x00000020
		 
    #define I2CONCLR_AAC     0x00000004  /* I2C Control clear Register */
    #define I2CONCLR_SIC     0x00000008
    #define I2CONCLR_STAC    0x00000020
    #define I2CONCLR_I2ENC   0x00000040

    #define I2DAT_I2C        0x00000000  /* I2C Data Reg */
    #define I2ADR_I2C        0x00000000  /* I2C Slave Address Reg */
    #define I2SCLH_SCLH      0x00000080  /* I2C SCL Duty Cycle High Reg */
    #define I2SCLL_SCLL      0x00000080  /* I2C SCL Duty Cycle Low Reg */
    /*
     * I2C总线结构体描述
     * {地址，电源(设置寄存器PCONP)，{引脚功能选择}}
     */
    #define I2C_A {\
         {{LPC_I2C0, 7, {&(LPC_PINCON->PINSEL1),0x01400000}}, {master}},\
         {{LPC_I2C1, 19, {&(LPC_PINCON->PINSEL0), 0xf}}, {master}},\
         {{LPC_I2C2, 26, {&(LPC_PINCON->PINSEL0), 0xaa << 20}}, {master}}\
    }
    struct i2c_s{
        LPC_I2C_TypeDef * const bus;
        const unsigned int pconp;
        const struct{
            volatile uint32_t * const pin_p;
            const unsigned int pin_v;
        } pin;
    };
    #define i2c_count() (sizeof(bus)/sizeof(bus[0]))
//    extern const struct i2c_manager_s * const i2c_bus_manager;
    #endif
#endif
