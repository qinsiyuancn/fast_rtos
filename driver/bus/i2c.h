/*
 * i2c.h
 * create by qinsiyuan
 * 			on 2016-7-26
 */

 #ifndef __I2C_H__
 #define __I2C_H__

	#include "i2c_lpc17xx.h"


	#define RW_BIT			0x01

	#define RD_BIT RW_BIT
	#define WR_BIT ~RW_BIT

	#define set_rdbit(addr) addr |= RD_BIT
	#define set_wrbit(addr)	addr &= WR_BIT

	/*
	 * i2c设备驱动公用的结构体
	 * 这个结构体描述的是文件层的结构，不是总线层的
	 */
	struct i2c_device{const unsigned char fd; const unsigned char slave_addr;};

	/*
	 * I2C会话
	 * 用于描述数据传输和数据控制
	 * 每个会话对应一个I2C数据总线非硬件部分
	 */
	struct i2c_session{
		struct{
			unsigned long size;//最大长度
			unsigned long proress;//当前进度
			unsigned char addr_rw;//丛地址，主模式时表示对方地址，从模式时表示自己的地址
			union {
				char * input;//读取消息缓冲区
				const char * output;
			}buffer_io;
		}msg;//传输数据描述
		struct{
			//unsigned char sem;
			OS_EVENT  * sem;//用于阻塞(同步)
//			OS_EVENT  * mutex;//用于独占(互斥)
		}ctrler;//控制描述
	};

	/*
	 * 设置从地址
	 * 主模式代表对端的从地址
	 * 从模式表示设置自己的从地址
	 * @param 总线序号
	 * @param 从地址
	 */
	void i2c_slave_address(unsigned char fd, unsigned char addr_rw);

	/*
	 * i2c读取
	 * @param 总线序号
	 * @param 数据缓存
	 * @param 缓存最大空间
	 * @return 实际写入总线的字节数
	 */
	unsigned long i2c_read(unsigned char fd, char * buffer, unsigned long size);

	/*
	 * i2c写
	 * @param 总线序号
	 * @param 写入总线的缓存
	 * @param 写入总线的字节数
	 * @return 实际写入总线的字节数
	 */
	unsigned long i2c_write(unsigned char fd, const char * buffer, unsigned long size);
	
	/*
	 * 初始化i2c总线硬件相关部分驱动
	 * @param 总线序号
	 * @param 主从模式
	 * @return
	 */
	unsigned char i2c_bus_init(unsigned char fd, enum i2c_mode mode);

	/*
	 * i2c初始化
	 * @param 总线序号
	 * @param 主从模式
	 * @return
	 */
	unsigned char i2c_init(unsigned char fd, enum i2c_mode mode);

	/*
	 * 从模式初始化
	 * @param 总线序号
	 * @param 自己的从地址
	 * @return 
	 */
	unsigned char i2c_init_slave(unsigned char fd, unsigned char addr);
	
	/*
	 * 主模式初始化
	 * @param 总线序号
	 * @return 
	 */
	unsigned char i2c_init_master(unsigned char fd);
 #endif
