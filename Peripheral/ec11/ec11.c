
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: ec11 code
 * 
 * ***************************************************************************/

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include <stdlib.h>

#include "ec11.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/

static void CallbackProcess(struct EC11 *this)
{
    switch (this->currentStatus)
    {
        case EC11_STATUS_FREE:
            if (0 == this->ReadA())
                this->currentStatus = EC11_STATUS_CCW_START;
            else if (0 == this->ReadB())
                this->currentStatus = EC11_STATUS_CW_START;
            break;

        case EC11_STATUS_CCW_START:
            if (0 == this->ReadB())
                this->currentStatus = EC11_STATUS_CCW_RUNNING;
            else if (0 != this->ReadA())
                this->currentStatus = EC11_STATUS_FREE;
            break;

        case EC11_STATUS_CCW_RUNNING:
            if (0 != this->ReadA())
                this->currentStatus = EC11_STATUS_CCW_WAIT;
            else if (0 != this->ReadB())
                this->currentStatus = EC11_STATUS_CCW_START;
            break;

        case EC11_STATUS_CCW_WAIT:
            if (0 != this->ReadB())
            {
                this->currentStatus = EC11_STATUS_FREE;
                this->sumCount--;
            }
            else if (0 == this->ReadA())
                this->currentStatus = EC11_STATUS_CCW_RUNNING;
            break;

        case EC11_STATUS_CW_START:
            if (0 == this->ReadA())
                this->currentStatus = EC11_STATUS_CW_RUNNING;
            else if (0 != this->ReadB())
                this->currentStatus = EC11_STATUS_FREE;
            break;
        
        case EC11_STATUS_CW_RUNNING:
            if (0 != this->ReadB())
                this->currentStatus = EC11_STATUS_CW_WAIT;
            else if (0 != this->ReadA())
                this->currentStatus = EC11_STATUS_CW_START;
            break;
        
        case EC11_STATUS_CW_WAIT:
            if (0 != this->ReadA())
            {
                this->currentStatus = EC11_STATUS_FREE;
                this->sumCount++;
            }
            else if (0 == this->ReadB())
                this->currentStatus = EC11_STATUS_CW_RUNNING;
            break;
    }
}

static inline int GetSumCount(struct EC11 *this)
{
    return this->sumCount;
}

static inline void SetSumCount(struct EC11 *this, int count)
{
    this->sumCount = count;
}

static inline unsigned int GetModCount(struct EC11 *this)
{
    return (this->sumCount % this->modulus);
}

struct EC11* EC11_Init(struct EC11_Init *initStruct)
{
    struct EC11 *ec11;

    if (NULL == initStruct)
        goto error;

    if (NULL == initStruct->HardwareInit 
        || NULL == initStruct->ReadA 
        || NULL == initStruct->ReadB)
        goto error;

    ec11 = (struct EC11 *)malloc(sizeof(*ec11));
    if (!ec11)
        goto error;

    initStruct->HardwareInit();
    ec11->ReadA = initStruct->ReadA;
    ec11->ReadB = initStruct->ReadB;
    if (0 == initStruct->modulus)
        ec11->modulus = 0xFFFFFFFF;
    else
        ec11->modulus = initStruct->modulus;

    ec11->sumCount = 0;
    ec11->currentStatus = EC11_STATUS_FREE;
    ec11->CallbackProcess = CallbackProcess;
    ec11->GetModCount = GetModCount;
    ec11->SetSumCount = SetSumCount;
    ec11->GetSumCount = GetSumCount;
    ec11->this = ec11;

    return ec11;
error:
    return NULL;
}

void EC11_Remove(struct EC11 *ec11)
{
    if (NULL == ec11)
        return;

    ec11->ReadA = NULL;
    ec11->ReadB = NULL;
    ec11->modulus = 0xFFFFFFFF;

    ec11->sumCount = 0;
    ec11->currentStatus = EC11_STATUS_FREE;
    ec11->GetModCount = NULL;
    ec11->SetSumCount = NULL;
    ec11->GetSumCount = NULL;
    ec11->CallbackProcess = NULL;
    ec11->this = NULL;

    free(ec11);
}

// User Create
struct EC11* EC11_Create(void)
{
    struct EC11_Init initStruct;

    initStruct.modulus = 10;
    initStruct.HardwareInit = EC11_PinInit;
    initStruct.ReadA = EC11_Read_A;
    initStruct.ReadB = EC11_Read_B;

    return EC11_Init(&initStruct);
}

