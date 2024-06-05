/*
 * i2c_lpc17xx.h
 * created by qinsiyuan
 * 		on 2016-6-29
 */

/*
 * 事件监听器
 */
extern unsigned int i2c_on_stop(unsigned char fd, unsigned char state);

extern unsigned char i2c_on_send_slave_addr(unsigned char fd, unsigned char state);

extern unsigned char i2c_on_send_data(unsigned char fd, unsigned char state);

extern unsigned char i2c_on_recv_ready(unsigned char fd, unsigned char state);

extern unsigned char i2c_on_recv_data(unsigned char fd, unsigned char state, unsigned char data);

extern unsigned int i2c_on_recv_last_data(unsigned char fd, unsigned char state, unsigned char data);

/*
 * i2c操作
 */
extern unsigned char i2c_getchar(unsigned char fd);

extern unsigned int i2c_send_recv(unsigned char fd, unsigned char addr, unsigned char * send_data, unsigned int send_size, unsigned char recv_data, unsigned int recv_size);

extern unsigned int i2c_recv(unsigned char fd, unsigned char addr, unsigned char * data, unsigned int size);

extern unsigned int i2c_send(unsigned char fd, unsigned char addr, const unsigned char * data, unsigned int size);

extern unsigned int i2c_stop(unsigned char fd);

extern unsigned int i2c_start(unsigned char fd, unsigned char addr, unsigned char * send_buffer, unsigned int send_size, unsigned char * recv_buffer, unsigned int recv_size);

extern int i2c_session_init(unsigned char fd);

extern int i2c_init_all();

#endif

