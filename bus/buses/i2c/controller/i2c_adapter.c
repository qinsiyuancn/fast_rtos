/*
 * i2c_lpc17xx.c
 * created by qinsiyuan
 * 		on 2016-6-29
 */

#include "i2c_adapter.h"
#include "i2c_session.h"
#define i2c_count() (sizeof(bus)/sizeof(bus[0]))

static struct {
    unsigned int fd;
    struct i2c_session session;
} bus[] = I2C_SESSION;

unsigned int i2c_on_stop(unsigned char fd, unsigned char state)
{
    FastRtosSemaphoreErrorCode error_code;
    if(fd < i2c_count())
        if(cpu_i2c_stop(fd)) {
            bus[fd].session.session.recv.buffer = NULL;
            bus[fd].session.session.recv.size = 0;
            bus[fd].session.session.send.buffer = NULL;
            bus[fd].session.session.send.size = 0;
            fast_rtos_sem_post(bus[fd].session.session.ctrl.finish);
            fast_rtos_mutex_unlock(bus[fd].session.session.ctrl.usingbus);
	    fast_rtos_sem_deinit(bus[fd].session.queue_size, error_code);
        }
    return 1;
}

unsigned char i2c_on_send_slave_addr(unsigned char fd, unsigned char state)
{
    /* A Start condition is issued. */
    return bus[fd].session.address << 1 | getbit(bus[fd].session.state_bitmap, read);
}

unsigned char i2c_on_send_data(unsigned char fd, unsigned char state)
{
    if (bus[fd].session.session.send.buffer && (bus[fd].session.session.send.size > bus[fd].session.current)) {
        clear_sic(fd);
//    i2c_base_transport_finish(i2c_bus_manager, fd);
//    I2CStop(fd);
//        bus[fd].i2cs.bus->I2DAT = bus[fd].session.session.send.buffer[current++];
        return bus[fd].session.session.send.buffer[current++];
    }
    clrbit(bus[fd].session.state_bitmap, write);
    if(getbit(bus[fd].session.state_bitmap, read)) {
        start(fd);
    } else {
        stop(fd, state);
    }
    return 0xff;
}


unsigned char i2c_on_recv_ready(unsigned char fd, unsigned char state)
{
/*    if(i2c_base_get_msg_size(i2c_bus_manager, fd) < 2){
        set_nack(fd);
    }else{
        set_ack(fd);
    }
    return 0;*/
    return getbit(bus[fd].session.state_bitmap, ack);
}

unsigned char i2c_on_recv_data(unsigned char fd, unsigned char state, unsigned char data)
{
    /*
    if (i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT) < 2) {
        set_nack(fd);
    }else{
        set_ack(fd);
    }
    */
    if (bus[fd].session.session.recv.buffer) {
        bus[fd].session.session.recv.buffer[bus[fd].session.current++] = data;
        if(fast_rtos_sem_enable(bus[fd].session.queue_size))fast_rtos_sem_post(bus[fd].session.queue_size);
        if (bus[fd].session.current == 2)
            clrbit(fd, ack);
    }
    return getbit(bus[fd].session.state_bitmap, ack);
}

unsigned int i2c_on_recv_last_data(unsigned char fd, unsigned char state, unsigned char data)
{
    // i2c_base_recv_char(i2c_bus_manager, fd, bus[fd]i2cs.bus->I2DAT);
    if (bus[fd].session.session.recv.buffer) {
        bus[fd].session.session.recv.buffer[bus[fd].session.current] = data;
    }
    stop(fd, state);
    return 0;
}

unsigned char i2c_getchar(unsigned char fd)
{
    unsigned int current = 0;
    unsigned int count = 0;
    if (fd < i2c_count) {
        if (fast_rtos_sem_enable(bus[fd].session.queue_size)) {
            fast_rtos_sem_wait(bus[fd].session.queue_size);
            do{
                clrbit(bus[fd].session.state_bitmap, interrupted);
                current = bus[fd].session.current;
                fast_rtos_sem_get_count(count, bus[fd].session.queue_size);
            }while(getbit(bus[fd].session.state_bitmap, interrupted));
            return bus[fd].session.session.recv.buffer[current - count - 1];
	}
    }
    return 0;
}

unsigned int i2c_send_recv(unsigned char fd, unsigned char addr, unsigned char * send_data, unsigned int send_size, unsigned char recv_data, unsigned int recv_size)
{
    FastRtosSemaphoreErrorCode error_code;
    if (fd < i2c_count) {
        if (send_data && send_size && recv_data && recv_size) {
            fast_rtos_mutex_lock(bus[fd].session.session.ctrl.usingbus, error_code);
            bus[fd].session.session.send.buffer = send_buffer;
            bus[fd].session.session.send.size = send_size;
            setbit(bus[fd].session.state_bitmap, write);

            bus[fd].session.session.recv.buffer = recv_buffer;
	    bus[fd].session.session.recv.size = recv_size;
            setbit(bus[fd].session.state_bitmap, read);

            bus[fd].session.address = addr;
            bus[fd].session.current = 0;
            recv_size < 2 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            cpu_i2c_start(fd);
            fast_rtos_sem_wait(bus[fd].session.session.ctrl.finish);
	}
	return 2;
    }
    return 1;
}

unsigned int i2c_recv(unsigned char fd, unsigned char addr, unsigned char * data, unsigned int size)
{
    FastRtosSemaphoreErrorCode error_code;
    if(fd < i2c_count()) {
        if(data && size){
            fast_rtos_mutex_lock(bus[fd].session.session.ctrl.usingbus, error_code);
            bus[fd].session.session.recv.buffer = data;
            bus[fd].session.session.recv.size = size;
            bus[fd].session.address = addr;
            size <= 1 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            setbit(bus[fd].session.state_bitmap, read);
            bus[fd].session.current = 0;
            start(fd);
            fast_rtos_sem_wait(bus[fd].session.session.ctrl.finish);
            return 0;
        }
        return 2;
    }
    return 1;
}

unsigned int i2c_send(unsigned char fd, unsigned char addr, const unsigned char * data, unsigned int size)
{
    
    FastRtosSemaphoreErrorCode error_code;
    if(fd < i2c_count()){
        if (data && size) {
            fast_rtos_mutex_lock(bus[fd].session.session.ctrl.usingbus, error_code);
            bus[fd].session.session.send.buffer = data;
            bus[fd].session.session.send.size = size;
            bus[fd].session.address = addr;
            size <= 1 ? clrbit(bus[fd].session.state_bitmap, setAck) : setbit(bus[fd].session.state_bitmap, setAck);
            setbit(bus[fd].session.state_bitmap, write);
            bus[fd].session.current = 0;
            cpu_i2c_start(fd);
            fast_rtos_sem_wait(bus[fd].session.session.ctrl.finish);
            return 0;
        }
        return 2;
    }
    return 1;
}

unsigned int i2c_stop(unsigned char fd)
{
    if (fd < i2c_count()) {
        clrbit(bus[fd].session.state_bitmap, setAck);
	return 0;
    }
    return 1;
}

unsigned int i2c_start(unsigned char fd, unsigned char addr, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    FastRtosSemaphoreErrorCode error_code;
    if(fd >= i2c_count())return 1;
    fast_rtos_mutex_lock(bus[fd].session.session.ctrl.usingbus, error_code);
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
    fast_rtos_sem_init(bus[fd].session.session.ctrl.finish, recv_size);
    return cpu_i2c_start(fd);
}

int i2c_session_init(unsigned char fd)
{
    FastRtosSemaphoreErrorCode error_code;
    if(fd >= i2c_count())return 1;
    fast_rtos_sem_init(bus[fd].session.session.ctrl.finish, 0);
    fast_rtos_lock_init(bus[fd].session.session.ctrl.usingbus, 0, error_code)
    return cpu_i2c_init(fd);
}

int i2c_init_all()
{
    unsigned int ret = 0;
    unsigned char i = 0;
    while(i < (sizeof(bus)/sizeof(bus[0]))) {
        ret = ret || i2c_session_init(i++);
    }
    return ret;
}

#endif

