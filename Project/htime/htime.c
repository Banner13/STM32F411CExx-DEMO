/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "htime.h"

/* *****************************************************************************
 *  init data
 * ****************************************************************************/
// 2023-04-23 22:53.34
enum SysDataMod {
    MOD_MILLISECOND = 1,
    MOD_SYS_SECOND  = 1000  *   MOD_MILLISECOND,
    MOD_SYS_MINUTE  = 60    *   MOD_SYS_SECOND,
    MOD_SYS_HOUR    = 60    *   MOD_SYS_MINUTE,
    MOD_SYS_DAY     = 24    *   MOD_SYS_HOUR,
};


/* *****************************************************************************
 *  golbal variables
 * ****************************************************************************/
volatile uint64_t g_system_tick = 0;

/* *****************************************************************************
 *  code
 * ****************************************************************************/
static inline void SetSysTick(uint32_t t) {g_system_tick = t;}
static inline uint32_t GetSysTick(void) {return g_system_tick;}

void DelayMs(uint32_t t)
{
    uint64_t time;
    time = GetSysTick() + t;
    while (time >= GetSysTick()) {};
}

void DelayS(uint32_t t)
{
    uint64_t time;
    time = GetSysTick() + t*1000;
    while (time >= GetSysTick()) {};
}

