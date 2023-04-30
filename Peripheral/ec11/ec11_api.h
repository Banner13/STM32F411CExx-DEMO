
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



/*                            api  prototype                                  */
void EC11_Init(void);

// EC11_Process: When interrupt A or B occurs, call it in the GPIO interrupt callback. 
void EC11_Process(void);
int EC11_GetCount(void);

#endif  // EC11_API_H

