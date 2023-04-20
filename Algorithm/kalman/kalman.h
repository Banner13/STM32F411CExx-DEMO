/* kalman process */
#ifndef HUKE_KALMAN_H
#define HUKE_KALMAN_H

/* *****************************************************************************
 *  include
 * ****************************************************************************/


/* ****************************************************************************
 *  API
 * ************************************************************************** */
void KalmanProcess(float meaV, float meaE, float* estV 
                            , float* estE, float* gain);


#endif // end define
