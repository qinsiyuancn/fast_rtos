/*
 * ttyS.c
 * create by qinsiyuan
 * 			on 2016-7-13
 * 将串口作为终端
 */
 #include "ttyS.h"

 static const char * const ttyS_filename = "ttyS";
 static unsigned char mode = 0;
 static unsigned long mode_param = 0;
 static const unsigned char ttyS_uart = BOARD_TTYS;

static int ttyS_open(const char * filename, int flags)
{
	if(strcmp(filename, ttyS_filename))return 0;
	return uart_use(ttyS_uart);
}

static int ttyS_close()
{
	uart_release(ttyS_uart);
	return 0;
}

static int ioctl(unsigned int request, unsigned long param)
{
	mode = (unsigned char)request;
	mode_param = param;
	return 1;		
}

static int ttyS_read_immediately(void *buf, unsigned long count)
{
	return (int)uart_read_clean(ttyS_uart, buf, count);	
}

static int ttyS_read_param(void *buf, unsigned long count)
{
	unsigned long param_count = mode_param;
	while(param_count-- && count--){
		*(((char *)buf) ++) = uart_getchar(ttyS_uart);
	}
	return mode_param - param_count;
}

static int ttyS_read_count(void *buf, unsigned long count)
{
	const unsigned long mcount = count;
	while(count--){
		*(((char *)buf) ++) = uart_getchar(ttyS_uart);	
	}
	return mcount;
}

static int ttyS_read_specific(void *buf, unsigned long count)
{
	unsigned long mcount = 0;
	for(mcount = 0;mcount < count && mode_param - *((char *)buf - 1); mcount ++){
		*(((char *)buf) ++) = uart_getchar(ttyS_uart);
	}
	return mcount;
}

static int ttyS_write(const void *buf, unsigned long count)
{
	return (int)uart_write( ttyS_uart, buf, count);	
}

typedef int (*read_method)(void *, unsigned long);

static const read_method read_collect[] = {ttyS_read_immediately, ttyS_read_param, ttyS_read_count, ttyS_read_specific};

static int ttyS_read(void *buf, unsigned long count)
{
	if(!buf)return 0;
	if(!count)return 0;
	#if 1 //牛X但不好用
	if(mode < sizeof(read_collect)/sizeof(read_collect[0])){
		return read_collect[mode](buf, count);	
	}
	return ttyS_read_immediately(buf, count);
	#else //好用单不牛X
		mode_param = '\r';
		return ttyS_read_specific(buf, count);
	#endif
}

const struct file_operation file_ttyS = {NULL, ttyS_open, ttyS_read, ttyS_write, ioctl, ttyS_close};

