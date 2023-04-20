/* *****************************************************************************
 *
 *  device abstraction
 *  author: huke
 *  date:   2023-4-8
 *  description: basic class of all peripherals
 * 
 * ****************************************************************************/

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "device.h"


/* *****************************************************************************
 *  code
 * ****************************************************************************/

int InitDevice(DeviceModel *device, const char* name ,Device_Op_t* op)
{
    if ((NULL == device) || (NULL == name) || (NULL == op) 
        || (NULL == op->Write)|| (NULL == op->Read))
        return -1;

    device->name = name;
    device->op.Write = op->Write;
    device->op.Read = op->Read;

    return 0;
}

const char* GetDeviceName(DeviceModel *device)
{
    return device->name;
}

int SetDeviceName(DeviceModel *device, const char* new_name)
{
    if (NULL == new_name)
        return -1;

    device->name = new_name;

    return 0;
}


