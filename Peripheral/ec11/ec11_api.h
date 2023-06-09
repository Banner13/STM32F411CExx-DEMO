
/* *****************************************************************************
 *
 *  ec11 rotary encoder driver
 *  author: huke
 *  date:   2023-4-30
 *  description: Application Interface
 * 
 * ***************************************************************************/
#ifndef EC11_API_H
#define EC11_API_H

#include "board.h"

/*                              User API define                              */
char EC11_Read_A(void);
char EC11_Read_B(void);
void EC11_PinInit(void);

#endif  // EC11_API_H

