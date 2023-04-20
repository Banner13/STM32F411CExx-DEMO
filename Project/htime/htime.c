/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "htime.h"

/* *****************************************************************************
 *  golbal variables
 * ****************************************************************************/
volatile uint32_t g_huke_sysTick;

/* *****************************************************************************
 *  code
 * ****************************************************************************/
static inline void SetSysTick(uint32_t t) {g_huke_sysTick = t;}
static inline uint32_t GetSysTick(void) {return g_huke_sysTick;}

inline void DelayUs(uint32_t t)
{
    SetSysTick(t);
    while (0 != GetSysTick()) {};
}

inline void DelayMs(uint32_t t)
{
    while (t--)
        DelayUs(1000);
}

inline void DelayS(uint32_t t)
{
    while (t--)
        DelayMs(1000);
}


