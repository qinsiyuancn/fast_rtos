#include "uart.h"
#include "uart_cpu.h"

const struct {
    FastRtosSemaphore semphore;
    const volatile uint32_t * pointer;
    unsigned int size;
    unsigned char buffer[DEFAULT_BUFFER_SIZE];
}session[] = UART_SESSION_INIT;

unsigned int uart_on_transport_finish(unsigned int fd)
{
    return 0;
}

unsigned int uart_on_recv_char(unsigned int fd, unsigned char data)
{
    pointer[session[fd].pos++ % session[fd].size] = data;
    fast_rtos_sem_post(session[fd].semphore);
    return 0;
}


static unsigned int stop(unsigned int dev)
{
    ErrorCode error_code[1] = {};
    session[dev].pointer = NULL;
    session[dev].pos = 0;
    fast_rtos_sem_deinit(session[dev].semphore, error_code);
    return 1;
}

static unsigned char getchar(unsigned int dev)
{
    if (pointer) {
        fast_rtos_sem_wait(session[dev].semphore);
        return session[dev].pointer[pos++ % session[dev].size];
    }
    return 0xff;
}

static unsigned int send(unsigned int dev, const unsigned char * data, unsigned int size)
{
    unsigned int i = 0;
    if(data)
        while(i < size)
            if(cpu_uart_send(dev, data[i++]))
                return i;
    return 0;
}

static unsigned int recv(unsigned int dev, unsigned char * data, unsigned int size)
{
    ErrorCode error_code[1] = {0};
    if (data && size) {
        fast_rtos_sem_init(session[dev].semphore, 0);
        session[fd].pointer = data;
        session[fd].pos = 0;
        while(size) {
            fast_rtos_sem_wait(session[fd].semphore);
            size--;
        }
        session[fd].pointer = NULL;
        session[fd].pos = 0;
        fast_rtos_sem_deinit(session[dev].semphore, error_code);
    }
    return 0;
}

static unsigned int send_recv(unsigned int dev, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size)
{
    if(send_data && send_size)
        send(dev, send_data, send_size);
    if(recv_data && recv_size)
        return recv(dev, recv_data, recv_size);
    return 0;
}


static unsigned int start(unsigned int dev, const unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size)
{
    session[dev].pointer = recv_buffer && recv_size ? recv_buffer : session[dev].buffer;
    session[dev].size = recv_buffer && recv_size ? recv_size : sizeof(session[dev].buffer) / sizeof(session[dev].buffer[0]);
    session[dev].pos = 0;
    fast_rtos_sem_init(session[dev].semphore, 0);
    return send_buffer && send_size ? send(dev, send_buffer, send_size) : 0;
}

static const struct bus bus = {"uart", {start, stop, getchar}, {send, recv, send_recv}};
const struct bus * const uart = &bus;
