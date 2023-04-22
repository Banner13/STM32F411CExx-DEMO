/* huke board api */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "board.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/
static inline void HUKE_RCC_Init()
{
    RCC_ClocksTypeDef RCC_ClockFreq;
    RCC_GetClocksFreq(&RCC_ClockFreq);

}

static inline void HUKE_GPIO_Init()
{

}

static inline void HUKE_SPI_Init()
{

}

static inline void HUKE_SysTick_Init()
{

}

static inline void HUKE_CRC_Init()
{

}

static inline void HUKE_ADC_Init()
{

}

static inline void HUKE_I2C_Init()
{

}

void BoardInit(void)
{

    HUKE_RCC_Init();
    HUKE_GPIO_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();
    HUKE_ADC_Init();
    HUKE_I2C_Init();

    HUKE_SysTick_Init();
}



