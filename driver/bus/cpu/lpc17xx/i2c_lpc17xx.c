/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c与cpu相关部分驱动
 */
#include "i2c_lpc17xx.h"

#if CPU_lpc17xx
static const struct i2c_s i2cs[] = I2C_A;

static unsigned int I2CStop( unsigned char fd )   
{   
  i2cs[fd].bus->I2CONSET = I2CONSET_STO;  /* Set Stop flag */    
  i2cs[fd].bus->I2CONCLR = I2CONCLR_SIC;  /* Clear SI flag */    
               
  /*--- Wait for STOP detected ---*/   
//  while( i2cs[fd].bus->I2CONSET & I2CONSET_STO );   
  return TRUE;   
}

static int clear_sic(unsigned char fd)
{
	i2cs[fd].bus->I2CONCLR = I2CONCLR_SIC;
	return 0;
}

static int set_ack(unsigned char fd)
{
	i2cs[fd].bus->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	clear_sic(fd);
	return 0;
}


static int set_nack(unsigned char fd)
{
	i2cs[fd].bus->I2CONCLR = I2CONCLR_SIC |I2CONCLR_AAC;
	return 0;
}

static int send_sla(unsigned char fd, unsigned char state)
{
	/* A Start condition is issued. */
	i2cs[fd].bus->I2DAT = i2c_base_get_addr(i2c_bus_manager, fd);   
	i2cs[fd].bus->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
	return 0;   
}

static int stop(unsigned char fd, unsigned char state)
{
	i2c_base_transport_finish(i2c_bus_manager, fd);
//	clear_sic(fd,state);
	I2CStop(fd);
	return 0;
}
static int send_data(unsigned char fd, unsigned char state)
{
	char ch[1] = {0};
	if(i2c_base_send_char(i2c_bus_manager, fd, ch)){
//		i2c_base_transport_finish(i2c_bus_manager, fd);
//		I2CStop(fd);
		stop(fd, state);
		return 1;
	}   
    i2cs[fd].bus->I2DAT = *ch;
    clear_sic(fd);
	return 0;
}

static int release_bus(unsigned char fd, unsigned char state)
{
	return clear_sic(fd);
}
static int recv_ready(unsigned char fd, unsigned char state)
{
	if(i2c_base_get_msg_size(i2c_bus_manager, fd) < 2){
		set_nack(fd);
	}else{
		set_ack(fd);	
	}
	return 0;
}

static int recv_data(unsigned char fd, unsigned char state)
{
	if(i2c_base_recv_char(i2c_bus_manager, fd, i2cs[fd].bus->I2DAT) < 2){
		set_nack(fd);	
	}else{
		set_ack(fd);			
	}
	return 0;
}
static int recv_last_data(unsigned char fd, unsigned char state)
{
	i2c_base_recv_char(i2c_bus_manager, fd, i2cs[fd].bus->I2DAT);
	stop(fd, state);
	return 0;	
}

static irq_funp const handler_state[0x20] = {
		/*0x00	由于非法起始或停止条件的出现，在MST或选择的从机模式中将出现总线错误。			 
		当外部干扰使I2C 模块进入未定义的状态时也出现0x00状态*/							NULL, 	  
		/*0x08	已发送起始条件*/														send_sla,  
		/*0x10	已发送重复的起始条件*/													send_sla, 
		/*0x18	已发送SLA+W，已接收ACK*/												send_data,
		/*0x20	已发送SLA+W，已接收非ACK*/												stop,
		/*0x28	已发送I2DAT中的数据字节，已接收ACK*/									send_data,	
		/*0x30	已发送I2DAT中的数据字节，已接收非ACK*/									stop,
		/*0x38	在SLA+R/W或数据字节中丢失仲裁，在非ACK位中丢失仲裁*/					release_bus,
		/*0x40	已发送SLA+R，已接收ACK*/												recv_ready,
		/*0x48	已发送SLA+R，已接收非ACK*/												stop,
		/*0x50	已接收数据字节，ACK已返回*/												recv_data,	
		/*0x58	已接收数据字节，非ACK已返回*/											recv_last_data,
};

static unsigned char i2c_work( unsigned char fd )   
{    
  if(fd > i2c_count())return 1;  
  /*--- Issue a start condition ---*/   
  i2cs[fd].bus->I2CONSET = I2CONSET_STA; /* Set Start flag */       
  /*--- Wait until START transmitted ---*/      
  return 0;   
}

static void I2C_IRQHandler(unsigned char fd)
{
	const unsigned i2c_stat = i2cs[fd].bus->I2STAT;
	if(handler_state[ i2c_stat >> 3])
		handler_state[ i2c_stat >> 3 ](fd, i2c_stat);
	else
		stop(fd, i2c_stat);
}

static int i2c_bus_init(unsigned char fd, enum i2c_mode mode)
{	
	if(fd >= i2c_count())return 1;
 
	LPC_SC->PCONP |= (1 << i2cs[fd].pconp);

	*(i2cs[fd].pin.pin_p) |= i2cs[fd].pin.pin_v;

	/*--- Clear flags ---*/   
	i2cs[fd].bus->I2CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;       
	   
	/*--- Reset registers ---*/   
	i2cs[fd].bus->I2SCLL = I2SCLL_SCLL;   
	i2cs[fd].bus->I2SCLH = I2SCLH_SCLH;   
          
	  /* Install interrupt handler */   
	NVIC_EnableIRQ(I2C0_IRQn + fd);
	if(mode){
		i2cs[fd].bus->I2CONSET = I2CONSET_I2EN;
	}else{
		i2cs[fd].bus->I2ADR0 = (i2c_base_get_addr(i2c_bus_manager, fd) & 0xfe) | (i2cs[fd].bus->I2ADR0 & 1);//只改地址，不改通用使能位   	
		i2cs[fd].bus->I2CONSET = I2CONSET_I2EN | I2CONSET_AA;
	}
	return 0;	
}


static const struct i2c_manager_s i2c_manager = {(sizeof(i2cs)/sizeof(i2cs[0])), i2c_bus_init, i2c_work, I2CStop, I2C_IRQHandler, &i2c_listener};
const struct i2c_manager_s * const i2c_bus_manager = &i2c_manager;
#endif

