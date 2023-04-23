/* huke board api */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "board.h"

/* *****************************************************************************
 *  code
 * ****************************************************************************/
// external 25MHz oscillator
// default use HSI is internal 16MHz 
static inline void HUKE_RCC_Init()
{
    RCC_ClocksTypeDef RCC_ClockFreq;

    RCC_DeInit();

    // PLL_out = PLL_in * (PLLN / PLLM) / PLLP
    // first config PLL target96MHz
    RCC_HSEConfig(RCC_HSE_ON);
    while (SET != RCC_GetFlagStatus(RCC_FLAG_HSERDY));

    FLASH_SetLatency(FLASH_Latency_2);

    RCC_HCLKConfig(RCC_SYSCLK_Div1); 

    RCC_PCLK2Config(RCC_HCLK_Div1); 

    RCC_PCLK1Config(RCC_HCLK_Div2);

    RCC_PLLConfig(RCC_PLLSource_HSE, 25, 192, 2, 4);

    RCC_PLLCmd(ENABLE);
    while (SET != RCC_GetFlagStatus(RCC_FLAG_PLLRDY));

    RCC_ClockSecuritySystemCmd(ENABLE);

    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (0x08 != RCC_GetSYSCLKSource());

    if (DEBUG) RCC_GetClocksFreq(&RCC_ClockFreq);
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



