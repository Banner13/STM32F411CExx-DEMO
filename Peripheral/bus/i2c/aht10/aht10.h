
/* *****************************************************************************
 *
 *  AHT10 driver
 *  author: huke
 *  date:   2023-4-2
 *  description: aht10 headfile
 * 
 * ***************************************************************************/
#ifndef I2C_DRIVER_AHT10_H
#define I2C_DRIVER_AHT10_H

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "i2c.h"
#include "aht10_api.h"


/* *****************************************************************************
*  definition
* *****************************************************************************/
#define AHT10_DEVICE_NAME   "aht10"
#define AHT10_I2C_ADDRES    (0x70)  // 0x38 << 1
/* *************************************
 * Reg List
 * ************************************/
typedef enum {
    AHT10_MEASURE           = 0xAC,
    AHT10_SOFT_RESET        = 0xBA,
    AHT10_INIT              = 0xE1,
    AHT10_GET_RESULT        = 0xFE,
    AHT10_STATUS            = 0xFF,
} AHT10_CMD;

typedef struct {
    unsigned char reserve1      : 3;
    unsigned char calEnable     : 1;
    unsigned char reserve2      : 1;
    unsigned char modeStatus    : 2;
    unsigned char busyFlag      : 1;
} AHT10_Status;

typedef struct {
    unsigned int humidity;
    unsigned int temperature;
} AHT10_Measure_Result;

struct AHT10 {
    I2C_Device_t i2c;
    void (*MsDelay)(unsigned int);
};
typedef struct AHT10 AHT10_t;
/* *****************************************************************************
*  prototype
* *****************************************************************************/

int InitDevice_AHT10(AHT10_t *aht10);
int AHT10_IOCTL(AHT10_t *aht10, AHT10_CMD cmd, void *data, unsigned int size);
#endif  // I2C_DRIVER_AHT10_H