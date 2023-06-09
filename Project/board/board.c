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
    GPIO_InitTypeDef   GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Mode    =   GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   =   GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin     =   GPIO_Pin_13 | GPIO_Pin_9 | GPIO_Pin_8 
                                        | GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 
                                        | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_PuPd    =   GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   =   GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_13);
}

static void HUKE_TIM3_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / 2000000) - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM3, ENABLE);
}

static void HUKE_SPI_Init()
{

}

static void HUKE_SysTick_Init()
{
    //  us_tick = Clock / 200 = 5ms
    if (SysTick_Config(SystemCoreClock / 200))
    { 
        /* Capture error */ 
        while (1);
    }
}

static void HUKE_CRC_Init()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
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
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
    DelayMs(500);
    
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
    DelayMs(500);

    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
    DelayMs(500);

    GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
    // GPIO Test end
#endif
}

void BoardInit(void)
{
    HUKE_RCC_Init();
    HUKE_GPIO_Init();
    HUKE_TIM3_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();
    HUKE_ADC_Init();
    HUKE_I2C_Init();

    HUKE_SysTick_Init();


    BoardBootTest();
}



