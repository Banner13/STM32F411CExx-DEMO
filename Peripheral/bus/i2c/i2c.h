
/* *****************************************************************************
 *
 *  I2C driver
 *  author: huke
 *  date:   2023-4-8
 *  description: I2C headfile
 * 
 * ****************************************************************************/

#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "bus.h"

/* *****************************************************************************
*  definition
* *****************************************************************************/
#define I2C_WRITE_FLAG  0
#define I2C_READ_FLAG   1

#define SOFTWARE_I2C    0
#define HARDWARE_I2C    1

#define I2C_ADDRES_7BIT     7
#define I2C_ADDRES_10BIT    10


struct Analog_I2C_Op {
    void (*SCL_Low)(void);
    void (*SCL_High)(void);
    void (*SDA_Low)(void);
    void (*SDA_High)(void);
    void (*SDA_Mode_R)(void);
    void (*SDA_Mode_W)(void);
    void (*Analog_I2C_UsDelay)(unsigned int);
    char (*SDA_Read)(void);
};
typedef struct Analog_I2C_Op Analog_I2C_Op_t;

struct I2C_Config {
    unsigned char mode; // analog i2c mode or hardware i2c mode
    unsigned char bit;
    unsigned char id_h; //  10bit addres hight      // 11110xx(r/w)
    unsigned char id_l; //  (7bit addres or) 10bit addres low  // xxxxxxx(r/w/x)
    unsigned int timeout;
};
typedef struct I2C_Config I2C_Config_t;


struct I2C_Device {
    Device_t            fd;
    I2C_Config_t        config;
    Analog_I2C_Op_t     analog_op;
};
typedef struct I2C_Device I2C_Device_t;

/* *****************************************************************************
*  prototype
* *****************************************************************************/
int InitDevice_I2C(I2C_Device_t *device, const char *name 
                            , I2C_Config_t *config, Analog_I2C_Op_t *analog_op);

#endif // I2C_DRIVER_H


