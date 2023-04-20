
/* *****************************************************************************
 *
 *  AHT10 driver
 *  author: huke
 *  date:   2023-4-8
 *  description: Application Interface
 * 
 * ****************************************************************************/

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "aht10_api.h"

// User headfile
#include "htime.h"
#include "board.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/
inline void AHT10_SCL_Low(void)
{
    // user code
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

inline void AHT10_SCL_High(void)
{
    // user code
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

inline void AHT10_SDA_Low(void)
{
    // user code
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

inline void AHT10_SDA_High(void)
{
    // user code
    GPIO_SetBits(GPIOB, GPIO_Pin_9);
}

void AHT10_SDA_Mode_R(void)
{
    // user code
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void AHT10_SDA_Mode_W(void)
{
    // user code
    
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

inline void AHT10_UsDelay(unsigned int t)
{
    // user code
    DelayUs(t);
}

inline void AHT10_MsDelay(unsigned int t)
{
    // user code
    DelayMs(t);
}

inline char AHT10_SDA_Read(void)
{
    // user code
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
}


