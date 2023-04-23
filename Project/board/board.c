/* huke board api */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "board.h"

#include "htime.h"
/* *****************************************************************************
 *  code
 * ****************************************************************************/
// external 25MHz oscillator
// default use HSI is internal 16MHz 
static void HUKE_RCC_Init()
{
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

    SystemCoreClockUpdate();
}

static void HUKE_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Mode   =   GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType  =   GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin    =   GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStruct.GPIO_PuPd   =   GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed  =   GPIO_Speed_2MHz;

    GPIO_WriteBit(GPIOB, GPIO_InitStruct.GPIO_Pin, Bit_RESET);

    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static void HUKE_SPI_Init()
{

}

static void HUKE_SysTick_Init()
{
    //  us_tick = Clock / 1000
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

static void HUKE_CRC_Init()
{

}

static void HUKE_ADC_Init()
{

}

static void HUKE_I2C_Init()
{

}

static void BoardBootTest()
{
#if (DEBUG)
    RCC_ClocksTypeDef RCC_ClockFreq;

    RCC_GetClocksFreq(&RCC_ClockFreq);

    // GPIO Test
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
    DelayMs(500);
    
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
    DelayMs(500);
    
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
    GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_SET);
    DelayMs(500);
    GPIO_WriteBit(GPIOB, GPIO_Pin_14, Bit_RESET);
    // GPIO Test end
#endif
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


    BoardBootTest();
}



