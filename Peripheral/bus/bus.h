/* *****************************************************************************
 *
 *  device abstraction
 *  author: huke
 *  date:   2023-4-8
 *  description: device abstraction headfile
 * 
 * ***************************************************************************/

#ifndef DEVICE_DRIVER_H
#define DEVICE_DRIVER_H

/* *****************************************************************************
 *  definition
 * ****************************************************************************/

#define DEVICE_NAME_MAX_SIZE    (20)

struct Device_Op {
    int (*Write)(const void* form, void* to, unsigned int size);
    int (*Read)(const void* form, void* to, unsigned int size);
};
typedef struct Device_Op Device_Op_t;

struct DeviceModel {
    char name[DEVICE_NAME_MAX_SIZE];
    Device_Op_t op;
};
typedef struct DeviceModel Device_t;

/* *****************************************************************************
 *  prototype
 * ****************************************************************************/

int InitDevice(Device_t *device, const char* name ,Device_Op_t* op);

const char* GetDeviceName(Device_t *device);

int SetDeviceName(Device_t *device, const char* new_name);


#endif  // DEVICE_DRIVER_H

