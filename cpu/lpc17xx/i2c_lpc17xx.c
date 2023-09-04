/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c与cpu相关部分驱动
 */
#include "i2c_lpc17xx.h"

#if CPU_lpc17xx
// static const struct i2c_s i2cs[] = I2C_A;
static struct {
    const struct i2c_s i2cs;
    struct i2c_session session;
} bus[] = I2C_A;

static unsigned int bus_stop( unsigned char fd ) 
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_STO;  /* Set Stop flag */
    bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_SIC;  /* Clear SI flag */
    /*--- Wait for STOP detected ---*/
    //  while( i2cs[fd].bus->I2CONSET & I2CONSET_STO );
    return TRUE;
}

static int clear_sic(unsigned char fd)
{
    bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_SIC;
    return 0;
}

static unsigned int stop(unsigned char fd, unsigned char state)
{
    if(fd < i2c_count())
        if(bus_stop(fd)) {
            bus[fd].session.session.recv.buffer = NULL;
            bus[fd].session.session.recv.size = 0;
            bus[fd].session.session.send.buffer = NULL;
            bus[fd].session.session.send.size = 0;
	    os_post(bus[fd].session.session.ctrl.finish);
	    os_unlock(bus[fd].session.session.ctrl.usingbus);
        }
    return 1;
}

static int set_ack(unsigned char fd)
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
    return clear_sic(fd);
}

static int set_nack(unsigned char fd)
{
    bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_SIC |I2CONCLR_AAC;
    return 0;
}

static int send_slave_addr(unsigned char fd, unsigned char state)
{
	/* A Start condition is issued. */
    bus[fd].i2cs.bus->I2DAT = bus[fd].session.address << 1 | getbit(bus[fd].session.state_bitmap, read) ;
    bus[fd].i2cs.bus->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
    return 0;
}

static int send_data(unsigned char fd, unsigned char state)
{
    static restart
    if (bus[fd].session.session.send.size > bus[fd].session.current) {
//    i2c_base_transport_finish(i2c_bus_manager, fd);
//    I2CStop(fd);
        bus[fd].i2cs.bus->I2DAT = bus[fd].session.session.send.buffer[current++];
        clear_sic(fd);
        return 0;
    }
    clrbit(bus[fd].session.state_bitmap, write);
    if(getbit(bus[fd].session.state_bitmap, read)) {
        start(fd);
    }
    else
        stop(fd, state);

    return 1;
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
    ack_set_list[getbit(bus[fd].session.state_bitmap, ack)](fd);
}

static int recv_data(unsigned char fd, unsigned char state)
{
    /*
    if (i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT) < 2) {
        set_nack(fd);
    }else{
        set_ack(fd);
    }
    */
    bus[fd].session.session.recv.buffer[bus[fd].session.current++] = bus[fd]i2cs.bus->I2DAT;
    ack_set_list[getbit(bus[fd].session.state_bitmap, ack)](fd);
    if (bus[fd].session.current == 2)
        clrbit(fd, ack);
    return 0;
}
static int recv_last_data(unsigned char fd, unsigned char state)
{
    // i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT);
    bus[fd].session.session.recv.buffer[bus[fd].session.current] = bus[fd]i2cs.bus->I2DAT;
    stop(fd, state);
    return 0;
}

static unsigned int start(unsigned char fd)
{
    if(fd >= i2c_count())return 1;
    /*--- Issue a start condition ---*/
    bus[fd]i2cs.bus->I2CONSET = I2CONSET_STA; /* Set Start flag */
    /*--- Wait until START transmitted ---*/
    return 0;
}

unsigned int i2c_send_recv(unsigned char fd, unsigned char addr, unsigned char * send_data, unsigned int send_size, unsigned char recv_data, unsigned int recv_size)
{
    if (fd < i2c_count) {
        if (send_data && send_size && recv_data && recv_size) {
            os_lock(bus[fd].session.session.ctrl.usingbus);
            bus[fd].session.session.send.buffer = send_buffer;
            bus[fd].session.session.send.size = send_size;
            setbit(bus[fd].session.state_bitmap, write);

            bus[fd].session.session.recv.buffer = recv_buffer;
	    bus[fd].session.session.recv.size = recv_size;
            setbit(bus[fd].session.state_bitmap, read);

            bus[fd].session.address = addr;
            bus[fd].session.current = 0;
            recv_size < 2 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            start(fd);
            os_wait(bus[fd].session.session.ctrl.finish);
	}
	return 2;
    }
    return 1;
}

unsigned int i2c_recv(unsigned char fd, unsigned char addr, unsigned char * data, unsigned int size)
{
    if(fd < i2c_count()) {
        if(data && size){
            os_lock(bus[fd].session.session.ctrl.usingbus);
            bus[fd].session.session.recv.buffer = data;
            bus[fd].session.session.recv.size = size;
            bus[fd].session.address = addr;
            size <= 1 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            setbit(bus[fd].session.state_bitmap, read);
            bus[fd].session.current = 0;
            start(fd);
            os_wait(bus[fd].session.session.ctrl.finish);
            return 0;
        }
        return 2;
    }
    return 1;
}

unsigned int i2c_send(unsigned char fd, unsigned char addr, const unsigned char * data, unsigned int size)
{
    if(fd < i2c_count()){
        if (data && size) {
            os_lock(bus[fd].session.session.ctrl.usingbus);
            bus[fd].session.session.send.buffer = data;
            bus[fd].session.session.send.size = size;
            bus[fd].session.address = addr;
            size <= 1 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            setbit(bus[fd].session.state_bitmap, write);
            bus[fd].session.current = 0;
            start(fd);
            os_wait(bus[fd].session.session.ctrl.finish);
            return 0;
        }
        return 2;
    }
    return 1;
}

unsigned int i2c_stop(unsigned char fd)
{
    if(fd >= i2c_count())return 1;
    clrbit(bus[fd].session.state_bitmap, setAck);
    return 0;
}

unsigned int i2c_start(unsigned char fd, unsigned char addr, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    if(fd >= i2c_count())return 1;
    os_lock(bus[fd].session.session.ctrl.usingbus);
    if(send_buffer && send_size){
        bus[fd].session.session.send.buffer = send_buffer;
        bus[fd].session.session.send.size = send_size;
        setbit(bus[fd].session.state_bitmap, write);
    }
    if(bus[fd].session.session.recv.buffer && recv_size){
        bus[fd].session.session.recv.buffer = recv_buffer;
	bus[fd].session.session.recv.size = recv_size;
    }else{
        bus[fd].session.session.recv.buffer = bus[fd].session.default_buffer;
	bus[fd].session.session.recv.size = sizeof(bus[fd].session.default_buffer) / sizeof(bus[fd].session.default_buffer[0]);
    }
    bus[fd].session.address = addr;
    bus[fd].session.current = 0;
    recv_size <= 1 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
    setbit(bus[fd].session.state_bitmap, read);
    return start(fd);
}

void I2C_IRQHandler(unsigned char fd)
{
    static irq_funp const handler_state[0x20] = {
        /*0x00 由于非法起始或停止条件的出现，在MST或选择的从机模式中将出现总线错误。			 
            当外部干扰使I2C 模块进入未定义的状态时也出现0x00状态*/  NULL, 	  
        /*0x08 已发送起始条件*/                                     send_slave_addr,  
        /*0x10 已发送重复的起始条件*/                               send_slave_addr, 
        /*0x18 已发送SLA+W，已接收ACK*/                             send_data,
        /*0x20 已发送SLA+W，已接收非ACK*/                           stop,
        /*0x28 已发送I2DAT中的数据字节，已接收ACK*/                 send_data,	
        /*0x30 已发送I2DAT中的数据字节，已接收非ACK*/               stop,
        /*0x38 在SLA+R/W或数据字节中丢失仲裁，在非ACK位中丢失仲裁*/ release_bus,
        /*0x40 已发送SLA+R，已接收ACK*/                             recv_ready,
        /*0x48 已发送SLA+R，已接收非ACK*/                           stop,
        /*0x50 已接收数据字节，ACK已返回*/                          recv_data,	
        /*0x58 已接收数据字节，非ACK已返回*/                        recv_last_data,
    };

    const unsigned char state = (bus[fd].i2cs.bus->I2STAT) >> 3;
    if(handler_state[ state ])
        handler_state[ state ](fd, stat);
    else
        stop(fd, i2c_stat);
}

static void set_mode_slave(unsigned int fd)
{
    bus[fd].i2cs.bus->I2ADR0 = (i2c_base_get_addr(i2c_bus_manager, fd) & 0xfe) | (bus[fd].i2cs.bus->I2ADR0 & 1);//只改地址，不改通用使能位
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN | I2CONSET_AA;
}

static void set_mode_master(unsigned int fd)
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN;
}

int i2c_bus_init(unsigned char fd)
{
    static void (* const set_mode[])(unsigned int) = {set_mode_slave, set_mode_master};

    if(fd >= i2c_count())return 1;

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

int i2c_bus_init_all()
{
    unsigned int ret = 0;
    unsigned char i = 0;
    while(i < (sizeof(bus)/sizeof(bus[0]))) {
        ret = ret || i2c_bus_init(i++);
    }
    return ret;
}

// static const struct i2c_manager_s i2c_manager = {(sizeof(i2cs)/sizeof(i2cs[0])), i2c_bus_init, i2c_work, I2CStop, I2C_IRQHandler, &i2c_listener};
// const struct i2c_manager_s * const i2c_bus_manager = &i2c_manager;
#endif

