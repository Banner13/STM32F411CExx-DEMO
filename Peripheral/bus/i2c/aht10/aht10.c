
/* *****************************************************************************
 *
 *  AHT10 driver
 *  author: huke
 *  date:   2023-4-2
 *  description: aht10 code
 * 
 * ****************************************************************************/

/* *****************************************************************************
*  include
* *****************************************************************************/
#include <stddef.h>
#include "aht10.h"
#include "aht10_api.h"

/* *****************************************************************************
*  definition
* *****************************************************************************/

/* *****************************************************************************
 *  code
 * ****************************************************************************/

int InitDevice_AHT10(AHT10_t *aht10)
{
    I2C_Config_t config;
    Analog_I2C_Op_t analog_op;

    if (NULL == aht10)
        return -1;

    aht10->MsDelay = AHT10_MsDelay;
    aht10->MsDelay(50);

    config.bit      = I2C_ADDRES_7BIT;
    config.id_l     = AHT10_I2C_ADDRES;
    config.mode     = SOFTWARE_I2C;
    config.timeout  = 10;

    analog_op.Analog_I2C_UsDelay    = AHT10_UsDelay;
    analog_op.SCL_High              = AHT10_SCL_High;
    analog_op.SCL_Low               = AHT10_SCL_Low;
    analog_op.SDA_High              = AHT10_SDA_High;
    analog_op.SDA_Low               = AHT10_SDA_Low;
    analog_op.SDA_Mode_R            = AHT10_SDA_Mode_R;
    analog_op.SDA_Mode_W            = AHT10_SDA_Mode_W;
    analog_op.SDA_Read              = AHT10_SDA_Read;

    return InitDevice_I2C(&aht10->i2c, AHT10_DEVICE_NAME , &config, &analog_op);
}

static int AHT10_Reset(AHT10_t *aht10)
{
    if (NULL == aht10) 
        return -1;

    char data = AHT10_SOFT_RESET;
    int res = 0;

    res = aht10->i2c.fd.op.Write(&data, &aht10->i2c, sizeof(data));

    aht10->MsDelay(25);

    return res;
}

static int AHT10_Init(AHT10_t *aht10)
{
    if (NULL == aht10) 
        return -1;

    char data[3] = {AHT10_INIT, 0x08, 0x00};

    return aht10->i2c.fd.op.Write(data, &aht10->i2c, sizeof(data));
}

static int AHT10_GetStatus(AHT10_t *aht10, AHT10_Status *status)
{
    if (NULL == aht10) 
        return -1;

    return aht10->i2c.fd.op.Read(&aht10->i2c, status, sizeof(*status));
}

static int AHT10_Measure(AHT10_t *aht10)
{
    if (NULL == aht10) 
        return -1;

    char data[3] = {AHT10_MEASURE, 0x33, 0x00};
    int res = 0;

    res = aht10->i2c.fd.op.Write(data, &aht10->i2c, sizeof(data));

    aht10->MsDelay(80);

    return res;
}

static int AHT10_GetResult(AHT10_t *aht10, AHT10_Measure_Result *result)
{
    if (NULL == aht10) 
        return -1;

    int res = 0;
    AHT10_Status status;
    unsigned char temp_result[6];
    unsigned int hum = 0;
    unsigned int temp = 0;
    char timeout = aht10->i2c.config.timeout;

    AHT10_GetStatus(aht10, &status);

    while ((1 == status.busyFlag) && timeout--)
    {
        aht10->MsDelay(25);
        AHT10_GetStatus(aht10, &status);
    }

    if (0 == timeout)
        return -2;

    res = aht10->i2c.fd.op.Read(&aht10->i2c, &temp_result, sizeof(temp_result));
    if (0 >= res)
        return -3;

    hum = (((unsigned int)temp_result[1] << 12) 
            | ((unsigned int)temp_result[2] << 4) 
            | ((unsigned int)temp_result[3] >> 4));
    temp = ((((unsigned int)temp_result[3] & 0x0F) << 16) 
            | ((unsigned int)temp_result[4] << 8) 
            | (unsigned int)temp_result[5]);

    hum = hum * 1000 / (1 << 20);
    temp = (temp * 2000 / (1 << 20)) - 500;

    result->humidity = hum;
    result->temperature = temp;

    return res;
}

int AHT10_IOCTL(AHT10_t *aht10, AHT10_CMD cmd, void *data, unsigned int size)
{
    int res = 0;

    switch (cmd)
    {
        case AHT10_MEASURE:
            res = AHT10_Measure(aht10);
            break;

        case AHT10_SOFT_RESET:
            res = AHT10_Reset(aht10);
            break;

        case AHT10_INIT:
            res = AHT10_Init(aht10);
            break;

        case AHT10_GET_RESULT:
            res = AHT10_GetResult(aht10, (AHT10_Measure_Result*)data);

        case AHT10_STATUS:
        default:
            res = AHT10_GetStatus(aht10, (AHT10_Status*)data);
            break;
    }

    return res;
}



