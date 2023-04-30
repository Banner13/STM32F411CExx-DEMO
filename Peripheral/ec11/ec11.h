
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: ec11 headfile
 * 
 * ***************************************************************************/
#ifndef EC11_H
#define EC11_H

#include "ec11_api.h"

/* *****************************************************************************
 *  definition
 * ****************************************************************************/
enum EC11_Status{
    EC11_STATUS_FREE        = 0,

    //  CCW Status
    EC11_STATUS_CCW_START   = 1,
    EC11_STATUS_CCW_RUNNING = 2,
    EC11_STATUS_CCW_WAIT    = 3,

    //  CW Status
    EC11_STATUS_CW_START    = 5,
    EC11_STATUS_CW_RUNNING  = 6,
    EC11_STATUS_CW_WAIT     = 7,
};

#endif  // EC11_H