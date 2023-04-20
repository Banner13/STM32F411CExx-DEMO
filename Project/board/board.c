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

    RCC_ClocksTypeDef clocksTypeDef;
    RCC_GetClocksFreq(&clocksTypeDef);
    RCC_GetClocksFreq(&clocksTypeDef);
    /* There is nothing to do, 
        as this is done in the bootloader's SystemInit function.
        72MHz
    */
}

static inline void HUKE_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 
                                | GPIO_Pin_2 | GPIO_Pin_3 
                                | GPIO_Pin_4 | GPIO_Pin_5 
                                | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_ResetBits(GPIOA, GPIO_InitStructure.GPIO_Pin);
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_ResetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static inline void HUKE_SPI_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStruct;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_Direction            = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode                 = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize             = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL                 = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA                 = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS                  = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler    = SPI_BaudRatePrescaler_4;
    SPI_InitStruct.SPI_FirstBit             = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial        = 10;
    SPI_Init(SPI1, &SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);
}

static inline void HUKE_SysTick_Init()
{
    //  us_tick = Clock / 1000 / 1000
    if (SysTick_Config(SystemCoreClock / 1000 / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
}

static inline void HUKE_CRC_Init()
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}

static inline void HUKE_ADC_Init()
{
    ADC_InitTypeDef ADC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_DeInit(ADC1);
    ADC_InitStruct.ADC_Mode                 = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode         = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode   = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign            = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel         = 0x01;
    ADC_Init(ADC1, &ADC_InitStruct);

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
     
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);

    while(ADC_GetCalibrationStatus(ADC1));
}

static inline void HUKE_I2C_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // I2C_InitTypeDef I2C_InitStruct;

    // GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_SetBits(GPIOB, GPIO_InitStructure.GPIO_Pin);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
/*
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    I2C_DeInit(I2C1);
    I2C_InitStruct.I2C_ClockSpeed           = 400000;
    I2C_InitStruct.I2C_Mode                 = I2C_Mode_I2C;
    I2C_InitStruct.I2C_DutyCycle            = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_OwnAddress1          = 0x00;
    I2C_InitStruct.I2C_Ack                  = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress  = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitStruct);

    I2C_Cmd(I2C1, ENABLE);
*/
}

void BoardInit(void)
{

    HUKE_RCC_Init();
    /*
    HUKE_GPIO_Init();
    HUKE_SPI_Init();
    HUKE_CRC_Init();
    HUKE_ADC_Init();
    
    HUKE_I2C_Init();
    */

    HUKE_SysTick_Init();
}



