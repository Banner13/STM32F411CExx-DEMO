/* huke help time */

/* *****************************************************************************
 *  include
 * ****************************************************************************/
#include "kalman.h"

/* *****************************************************************************
 *  golbal variables
 * ****************************************************************************/


/* *****************************************************************************
 *  code
 * ****************************************************************************/

inline float GetKalmanGain(float meaE, float estE)
{
    return (estE/(meaE+estE));
}

inline float GetKalmanEstValue(float meaV, float estV, float gain)
{
    return (estV + gain * (meaV - estV));
}

inline float UpdateEest(float lastEest, float gain)
{
    return ((1 - gain) * lastEest);
}

inline void KalmanProcess(float meaV, float meaE, float* estV 
                                , float* estE, float* gain)
{
    *gain = GetKalmanGain(meaE, *estE);
    *estV = GetKalmanEstValue(meaV, *estV, *gain);
    *estE = UpdateEest(*estE, *gain);
}

