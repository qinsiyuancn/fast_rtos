/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 * 		on 2016-6-29
 * i2c��cpu��ز�������
 */
#include "i2c_lpc17xx.h"

#if CPU_lpc17xx
// static const struct i2c_s i2cs[] = I2C_A;
static struct {
    const struct i2c_s i2cs;
    struct i2c_session session;
} bus[] = I2C_A;

static unsigned int I2CStop( unsigned char fd ) 
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

static int set_ack(unsigned char fd)
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
    clear_sic(fd);
    return 0;
}


static int set_nack(unsigned char fd)
{
    bus[fd].i2cs.bus->I2CONCLR = I2CONCLR_SIC |I2CONCLR_AAC;
    return 0;
}

static int send_sla(unsigned char fd, unsigned char state)
{
	/* A Start condition is issued. */
    bus[fd].i2cs.bus->I2DAT = i2c_base_get_addr(i2c_bus_manager, fd);
    bus[fd].i2cs.bus->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
    return 0;
}

static int send_data(unsigned char fd, unsigned char state)
{
    char ch[1] = {0};
    if(i2c_base_send_char(i2c_bus_manager, fd, ch)){
//    i2c_base_transport_finish(i2c_bus_manager, fd);
//    I2CStop(fd);
        stop(fd, state);
        return 1;
    }
    bus[fd].i2cs.bus->I2DAT = *ch;
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
    if (i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT) < 2) {
        set_nack(fd);
    }else{
        set_ack(fd);
    }
    return 0;
}
static int recv_last_data(unsigned char fd, unsigned char state)
{
    i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT);
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

unsigned int i2c_start(unsigned char fd )
{
    if(fd >= i2c_count())return 1;
    bus[fd].session.buffer.buffer = bus[fd].session.buffer.default_buffer;
    bus[fd].session.buffer.current = 0;
    bus[fd].session.buffer.size = 0;
    return start(fd);
}

unsigned int i2c_stop(unsigned char fd, unsigned char state)
{
    // i2c_base_transport_finish(i2c_bus_manager, fd);
//    clear_sic(fd,state);
    if(fd < i2c_count())
        if(!stop(fd)) {
            bus[fd].session.buffer.buffer = NULL;
            bus[fd].session.buffer.current = 0;
            bus[fd].session.buffer.size = 0;
        }
    return 1;
}

void I2C_IRQHandler(unsigned char fd)
{
    static irq_funp const handler_state[0x20] = {
        /*0x00 ���ڷǷ���ʼ��ֹͣ�����ĳ��֣���MST��ѡ��Ĵӻ�ģʽ�н��������ߴ���			 
            ���ⲿ����ʹI2C ģ�����δ�����״̬ʱҲ����0x00״̬*/  NULL, 	  
        /*0x08 �ѷ�����ʼ����*/                                     send_sla,  
        /*0x10 �ѷ����ظ�����ʼ����*/                               send_sla, 
        /*0x18 �ѷ���SLA+W���ѽ���ACK*/                             send_data,
        /*0x20 �ѷ���SLA+W���ѽ��շ�ACK*/                           stop,
        /*0x28 �ѷ���I2DAT�е������ֽڣ��ѽ���ACK*/                 send_data,	
        /*0x30 �ѷ���I2DAT�е������ֽڣ��ѽ��շ�ACK*/               stop,
        /*0x38 ��SLA+R/W�������ֽ��ж�ʧ�ٲã��ڷ�ACKλ�ж�ʧ�ٲ�*/ release_bus,
        /*0x40 �ѷ���SLA+R���ѽ���ACK*/                             recv_ready,
        /*0x48 �ѷ���SLA+R���ѽ��շ�ACK*/                           stop,
        /*0x50 �ѽ��������ֽڣ�ACK�ѷ���*/                          recv_data,	
        /*0x58 �ѽ��������ֽڣ���ACK�ѷ���*/                        recv_last_data,
    };

    const unsigned i2c_stat = bus[fd].i2cs.bus->I2STAT;
    if(handler_state[ i2c_stat >> 3])
        handler_state[ i2c_stat >> 3 ](fd, i2c_stat);
    else
        stop(fd, i2c_stat);
}

static void set_slave(unsigned int fd)
{
    bus[fd].i2cs.bus->I2ADR0 = (i2c_base_get_addr(i2c_bus_manager, fd) & 0xfe) | (bus[fd].i2cs.bus->I2ADR0 & 1);//ֻ�ĵ�ַ������ͨ��ʹ��λ
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN | I2CONSET_AA;
}

static void set_master(unsigned int fd)
{
    bus[fd].i2cs.bus->I2CONSET = I2CONSET_I2EN;
}

int i2c_bus_init(unsigned char fd)
{
    static void (* const set_mode[])(unsigned int) = {set_slave, set_master};

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
