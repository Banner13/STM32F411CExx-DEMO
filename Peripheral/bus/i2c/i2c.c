/* *****************************************************************************
 *
 *  I2C driver
 *  author: huke
 *  date:   2023-4-8
 *  description: I2C src file
 * 
 * ****************************************************************************/

/* *****************************************************************************
*  include
* *****************************************************************************/
#include <stdbool.h>
#include <string.h>
#include "i2c.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/

void I2C_Start(I2C_Device_t *device)
{
    // release SCL
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    // init status
    device->analog_op.SDA_Mode_W();
    device->analog_op.SDA_High();
    device->analog_op.Analog_I2C_UsDelay(5);

    device->analog_op.SCL_High();
    device->analog_op.Analog_I2C_UsDelay(5);

    // start flag
    device->analog_op.SDA_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
}

void I2C_Stop(I2C_Device_t *device)
{
    // release SCL
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    // init status
    device->analog_op.SDA_Mode_W();
    device->analog_op.SDA_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SCL_High();
    device->analog_op.Analog_I2C_UsDelay(5);

    // end flag
    device->analog_op.SDA_High();
    device->analog_op.Analog_I2C_UsDelay(5);
}

void I2C_SendACK(I2C_Device_t *device)
{
    // release SCL
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    // init status
    device->analog_op.SDA_Mode_W();

    // send ACK
    device->analog_op.SDA_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SCL_High();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
}

void I2C_SendNACK(I2C_Device_t *device)
{
    // release SCL
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    // init status
    device->analog_op.SDA_Mode_W();

    // send NACK
    device->analog_op.SDA_High();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SCL_High();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
}

bool I2C_ReciveACK(I2C_Device_t *device)
{
    unsigned short timeout = 0;
    static volatile unsigned char res = 1;

    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);
    device->analog_op.SDA_Mode_R();


    device->analog_op.SCL_High();
    device->analog_op.Analog_I2C_UsDelay(5);

	while ((res = device->analog_op.SDA_Read()) && timeout++ < 100);
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    return !res;
}


void I2C_SendByte(I2C_Device_t *device, char byte)
{
    char i = 0;

    // release SCL
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    device->analog_op.SDA_Mode_W();

    while (i < 8)
    {
        if ((byte << i) & 0x80)
            device->analog_op.SDA_High();
        else
            device->analog_op.SDA_Low();

        device->analog_op.SCL_High();
        device->analog_op.Analog_I2C_UsDelay(5);

        device->analog_op.SCL_Low();
        device->analog_op.Analog_I2C_UsDelay(5);

        i++;
    }
}

char I2C_ReciveByte(I2C_Device_t *device)
{
    //return I2CC_ReciveByte();
    int i = 8;
    unsigned char data = 0x00;

    // init status
    device->analog_op.SCL_Low();
    device->analog_op.Analog_I2C_UsDelay(5);

    device->analog_op.SDA_Mode_R();

    while (i--)
    {
        device->analog_op.SCL_High();
        device->analog_op.Analog_I2C_UsDelay(5);

        if (device->analog_op.SDA_Read())
            data |= (0x01 << i);

        device->analog_op.SCL_Low();
        device->analog_op.Analog_I2C_UsDelay(5);

    }

    return data;
}

int I2C_SendAddres(I2C_Device_t *device, unsigned char direction)
{
    char addres[2];
    unsigned char i = 1;
    unsigned res = 0;

    addres[0] = device->config.id_h;
    addres[1] = device->config.id_l;

    if (10 == device->config.bit)
        i = 0;

    if (I2C_READ_FLAG == direction)
        addres[i] |= 0x01;
    else
        addres[i] &= ~(0x01);

    if (10 == device->config.bit)
    {
        I2C_SendByte(device, addres[0]);
        if (!I2C_ReciveACK(device))
            res |= -1;
    }

    I2C_SendByte(device, addres[1]);
    if (!I2C_ReciveACK(device))
        res |= -1;

    return res;
}

int I2C_Send(const void* form, void* to, unsigned int size)
{
    int i = 0;
    I2C_Device_t *device = (I2C_Device_t*)to;
    char *data = (char*)form;

    if ((NULL == device) || (NULL == data))
        return -1;

    I2C_Start(device);

    if (0 <= I2C_SendAddres(device, I2C_WRITE_FLAG))
    {
        while (i < size)
        {
            I2C_SendByte(device, data[i]);
            if (!I2C_ReciveACK(device))
                break;
            i++;
        }
    }
    I2C_Stop(device);
    return i;
}

int I2C_Recive(const void* form, void* to, unsigned int size)
{
    int i = 0;
    I2C_Device_t *device = (I2C_Device_t*)form;
    char *data = (char*)to;

    if ((NULL == device) || (NULL == data))
        return -1;

    I2C_Start(device);

    if (0 <= I2C_SendAddres(device, I2C_READ_FLAG))
    {
        while (i < size-1)
        {
            data[i] = I2C_ReciveByte(device);
            I2C_SendACK(device);
            i++;
        }
        data[i] = I2C_ReciveByte(device);
        I2C_SendNACK(device);
        i++;
    }
    I2C_Stop(device);
    return i;
}

int InitDevice_I2C(I2C_Device_t *device, const char *name 
                            , I2C_Config_t *config, Analog_I2C_Op_t *analog_op)
{
    if ((NULL == device) || (NULL == name) || (NULL == config))
        return -1;

    device->config.mode     = config->mode;
    device->config.bit      = config->bit;
    device->config.id_h     = config->id_h;
    device->config.id_l     = config->id_l;
    device->config.timeout  = config->timeout;

    if (SOFTWARE_I2C == device->config.mode)
    {
        if ((NULL == analog_op) || (NULL == analog_op->Analog_I2C_UsDelay) 
            || (NULL == analog_op->SCL_High) || (NULL == analog_op->SCL_Low) 
            || (NULL == analog_op->SDA_High) || (NULL == analog_op->SDA_Low) 
            || (NULL == analog_op->SDA_Mode_R) || (NULL == analog_op->SDA_Mode_W)
            || (NULL == analog_op->SDA_Read))
            return -2;

        memcpy((void*)&device->analog_op, analog_op, sizeof(*analog_op));

        device->fd.op.Write = I2C_Send;
        device->fd.op.Read = I2C_Recive;
    }
    strncpy(device->fd.name, name, DEVICE_NAME_MAX_SIZE);

    return 0;
}



