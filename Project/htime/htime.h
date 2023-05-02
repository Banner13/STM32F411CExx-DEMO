/* huke help time */
#ifndef HUKE_HTIME_H
#define HUKE_HTIME_H

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include <stdint.h>


/* ****************************************************************************
 *  definition
 * ************************************************************************** */


/* ****************************************************************************
 *  API
 * ************************************************************************** */
void Htime_Init(void);
/*   TIM3 Channel1  */
void DelayUs(uint32_t t);
void DelayMs(uint32_t t);

/*   system tick  */
void Delay5Ms(uint32_t t);
void DelayS(uint32_t t);


#endif // end define
