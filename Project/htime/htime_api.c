
#include "htime_api.h"

void Timer_Init(void)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
}


void Timer_Start(uint32_t count)
{
    count <<= 1;
    count += TIM_GetCounter(TIM3);
    if (count >= 0xFFFF)
        count -= 0xFFFF;

    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    TIM_SetCompare1(TIM3, count);
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
}

