/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 *     on 2016-6-2
 * i2c与cpu相关驱动部分
 */
#include "i2c_lpc17xx.h"

#if CPU_lpc17xx
    static const struct i2c_s bus[] = I2C_A;

unsigned int cpu_i2c_stop(unsigned char fd)
{
    if (fd < (sizeof(bus)/sizeof(bus[0]))) {
        bus[fd].bus->I2CONSET = I2CONSET_STO;  /* Set Stop flag */
        bus[fd].bus->I2CONCLR = I2CONCLR_SIC;  /* Clear SI flag */
        /*--- Wait for STOP detected ---*/
        //  while( i2cs[fd].bus->I2CONSET & I2CONSET_STO );
        return TRUE;
	}
	return FALSE;
}

unsigned int cpu_i2c_clear_sic(unsigned char fd)
{
    if (fd < (sizeof(bus)/sizeof(bus[0]))) {
        bus[fd].bus->I2CONCLR = I2CONCLR_SIC;
	}
    return 0;
}

static int stop(unsigned char fd, unsigned char state)
{
    i2c_on_stop(fd, state);
    return 1;
}

static int set_ack(unsigned char fd)
{
    if (fd < (sizeof(bus)/sizeof(bus[0]))) {
        bus[fd].i2cs.bus->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
        return clear_sic(fd);
	}
	return FALSE;
}

static int set_nack(unsigned char fd)
{
    if (fd < (sizeof(bus)/sizeof(bus[0])))
        bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_SIC |I2CONCLR_AAC;
    return TRUE;
}

static int send_slave_addr(unsigned char fd, unsigned char state)
{
    if (fd < (sizeof(bus)/sizeof(bus[0]))) {
	    /* A Start condition is issued. */
        bus[fd].i2cs.bus->I2DAT = i2c_on_send_slave_addr(fd, state) ;
        bus[fd].i2cs.bus->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		return TRUE;
	}
    return FALSE;
}

static int send_data(unsigned char fd, unsigned char state)
{
    if (fd < (sizeof(bus)/sizeof(bus[0]))) {
        bus[fd].i2cs.bus->I2DAT = i2c_on_send_data(fd,state);
        clear_sic(fd);
        return TRUE;
    }
    return FALSE;
}

static int release_bus(unsigned char fd, unsigned char state)
{

    return clear_sic(fd);
}

static int (* const ack_set_list[])(unsigned char) = {set_nack, set_ack};

static int recv_ready(unsigned char fd, unsigned char state)
{
/*    if(i2c_base_get_msg_size(i2c_bus_manager, fd) < 2){
        set_nack(fd);
    }else{
        set_ack(fd);
    }
    return 0;*/
    if (fd < (sizeof(bus)/sizeof(bus[0])))
        return ack_set_list[i2c_on_recv_ready(fd, state)](fd);
	return FALSE;
}

static int recv_data(unsigned char fd, unsigned char state)
{
    if (fd < (sizeof(bus)/sizeof(bus[0])))
        return ack_set_list[i2c_on_recv_data(fd, state, bus[fd].bus->I2DAT), ack](fd);
    return FALSE;
}
static int recv_last_data(unsigned char fd, unsigned char state)
{
    if (fd < (sizeof(bus)/sizeof(bus[0])))
	    return i2c_on_recv_last_data(fd, state, bus[fd]i2cs.bus->I2DAT);
    return FALSE;
}

unsigned int cpu_i2c_start(unsigned char fd)
{
    if(fd >= i2c_count())return 1;
    /*--- Issue a start condition ---*/
    bus[fd]i2cs.bus->I2CONSET = I2CONSET_STA; /* Set Start flag */
    /*--- Wait until START transmitted ---*/
    return 0;
}




void I2C_IRQHandler(unsigned char fd)
{
    static irq_funp const handler_state[0x20] = {
    /*0x00 由于非法起始或停止条件的出现，在MST或选择的丛集模式中出现总线错误。
	       当外部干扰使I2C 模块进入未定义的状态时也出现0x00状态*/     NULL,
	/*0x08 已发送起始条件*/                                           send_slave_addr,
	/*0x10 已发送重复的起始条件*/                                     send_slave_addr,
	/*0x18 已发送SLA+W, 已接收ACK*/                                   send_data,
	/*0x20 已发送SLA+W, 已接收非ACK(nack)*/                           stop,
	/*0x28 已发送I2DAT中的数据字节，已接收ACK*/                       send_data,
	/*0x30 已发送I2DAT中的数据字节，已接收非ACK(nack)*/               stop,
	/*0x38 在SLA+R/W或数据字节中丢失仲裁，在非ACK(nack)位中丢失仲裁*/ release_bus,
	/*0x40 已发送SLA+R, 已接收ACK*/                                   recv_ready,
	/*0x48 已发送SLA+R, 已接收非ACK(nack)*/                           stop,
	/*0x50 已接收数据字节，已返回ACK*/                                recv_data,
	/*0x58 已接收数据字节，已返回非ACK(nack)*/                        recv_last_data,
    };

    const unsigned char state = (bus[fd].i2cs.bus->I2STAT) >> 3;
    if(handler_state[ state ])
        handler_state[ state ](fd, stat);
    else
        stop(fd, i2c_stat);
}

static void set_mode_slave(unsigned int fd)
{
    //bus[fd].i2cs.bus->I2ADR0 = (i2c_base_get_addr(i2c_bus_manager, fd) & 0xfe) | (bus[fd].i2cs.bus->I2ADR0 & 1);
    bus[fd].i2cs.bus->I2ADR0 = bus[fd].session.address << 1 | (bus[fd].i2cs.bus->I2ADR0 & 1); // 只改地址，不改通用使能位
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN | I2CONSET_AA;
}

static void set_mode_master(unsigned int fd)
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN;
}

unsigned int cpu_i2c_init(unsigned char fd)
{
    static void (* const set_mode[])(unsigned int) = {set_mode_slave, set_mode_master};
    FastRtosSemaphoreErrorCode error_code;
    if(fd >= i2c_count())return 1;
    fast_rtos_sem_init(bus[fd].session.session.ctrl.finish, 0);
    fast_rtos_lock_init(bus[fd].session.session.ctrl.usingbus, 0, error_code)
    LPC_SC->PCONP |= (1 << bus[fd].i2cs.pconp);

    *(bus[fd].i2cs.pin.pin_p) |= bus[fd].i2cs.pin.pin_v;

    /*--- Clear flags ---*/
    bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;

    /*--- Reset registers ---*/
    bus[fd].i2cs.bus->I2SCLL = I2SCLL_SCLL;
    bus[fd].i2cs.bus->I2SCLH = I2SCLH_SCLH;

    /* Install interrupt handler */
    NVIC_EnableIRQ(I2C0_IRQn + fd);

    set_mode[bus[fd].config.mode](fd);
    return 0;
}

// static const struct i2c_manager_s i2c_manager = {(sizeof(i2cs)/sizeof(i2cs[0])), i2c_bus_init, i2c_work, I2CStop, I2C_IRQHandler, &i2c_listener};
// const struct i2c_manager_s * const i2c_bus_manager = &i2c_manager;
#endif

