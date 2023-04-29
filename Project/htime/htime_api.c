
#include "htime_api.h"

void TimerStart(uint32_t count)
{
    TIM_SetCompare1(TIM3, count);
    TIM_Cmd(TIM3, ENABLE);
}

