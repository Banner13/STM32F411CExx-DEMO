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
}

static void HUKE_TIM3_Init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

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

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
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
    HUKE_TIM3_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();
    HUKE_ADC_Init();
    HUKE_I2C_Init();

    HUKE_SysTick_Init();


    BoardBootTest();
}



