#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

extern unsigned int device_start(unsigned int device, const unsigned char * send_buffer, unsigned int send_size, unsigned char* recv_buffer, unsigned int recv_size);

extern unsigned int device_stop(unsigned int device);

extern unsigned char device_getchar(unsigned int device);

extern unsigned short device_getshort(unsigned int device);

extern unsigned long device_getlong(unsigned int device);

extern unsigned int device_send(unsigned int device, unsigned char * buffer, unsigned int count);

extern unsigned int device_recv(unsigned int device, unsigned char * buffer, unsigned int count);

extern unsigned int device_send_recv(unsigned int device, const unsigned char * send_data, unsigned int send_size, unsigned char * recv_data, unsigned int recv_size);

#endif
