#include <stdio.h>
#include <string.h>
#include "board.h"
#include "htime.h"
#include "ec11.h"
#include "display.h"


/* *****************************************************************************
 *  globel variables
 * ****************************************************************************/
// It's not only
struct EC11* g_ec11;

int main(void)
{
    int count = 0;
    BoardInit();
    Htime_Init();
    DisplayInit();


    g_ec11 = EC11_Create();
    DisplayTest();

    while (1)
    {
        count = g_ec11->GetSumCount(g_ec11->this);
    }

    return count;
}
