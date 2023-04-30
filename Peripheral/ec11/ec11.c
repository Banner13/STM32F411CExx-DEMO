
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: ec11 code
 * 
 * ***************************************************************************/

#include "ec11.h"

/* *****************************************************************************
 *  globel variable
 * ****************************************************************************/
static volatile unsigned int g_ec11_status;
static int g_ec11_count;


/* *****************************************************************************
 *  code
 * ****************************************************************************/
void EC11_Init(void)
{
    EC11_PinInit();

    g_ec11_status = EC11_STATUS_FREE;
    g_ec11_count = 0;
}

void EC11_Process(void)
{
    switch (g_ec11_status)
    {
        case EC11_STATUS_FREE:
            if (0 == EC11_Read_A())
                g_ec11_status = EC11_STATUS_CCW_START;
            else if (0 == EC11_Read_B())
                g_ec11_status = EC11_STATUS_CW_START;
            break;

        case EC11_STATUS_CCW_START:
            if (0 == EC11_Read_B())
                g_ec11_status = EC11_STATUS_CCW_RUNNING;
            else if (0 != EC11_Read_A())
                g_ec11_status = EC11_STATUS_FREE;
            break;

        case EC11_STATUS_CCW_RUNNING:
            if (0 != EC11_Read_A())
                g_ec11_status = EC11_STATUS_CCW_WAIT;
            else if (0 != EC11_Read_B())
                g_ec11_status = EC11_STATUS_CCW_START;
            break;

        case EC11_STATUS_CCW_WAIT:
            if (0 != EC11_Read_B())
            {
                g_ec11_status = EC11_STATUS_FREE;
                g_ec11_count--;
            }
            else if (0 == EC11_Read_A())
                g_ec11_status = EC11_STATUS_CCW_RUNNING;
            break;

        case EC11_STATUS_CW_START:
            if (0 == EC11_Read_A())
                g_ec11_status = EC11_STATUS_CW_RUNNING;
            else if (0 != EC11_Read_B())
                g_ec11_status = EC11_STATUS_FREE;
            break;
        
        case EC11_STATUS_CW_RUNNING:
            if (0 != EC11_Read_B())
                g_ec11_status = EC11_STATUS_CW_WAIT;
            else if (0 != EC11_Read_A())
                g_ec11_status = EC11_STATUS_CW_START;
            break;
        
        case EC11_STATUS_CW_WAIT:
            if (0 != EC11_Read_A())
            {
                g_ec11_status = EC11_STATUS_FREE;
                g_ec11_count++;
            }
            else if (0 == EC11_Read_B())
                g_ec11_status = EC11_STATUS_CW_RUNNING;
            break;
    }
}

inline int EC11_GetCount(void)
{
    return g_ec11_count;
}

