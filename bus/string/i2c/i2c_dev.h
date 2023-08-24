#ifndef __I2C_DEVICE_H__
#define __I2C_DEVICE_H__
    
    struct i2c_device{
        const unsigned int bus_index;
        const unsigned char slave_addr;
    };

#endif
