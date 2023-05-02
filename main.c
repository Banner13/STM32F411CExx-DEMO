#include <stdio.h>
#include <string.h>
#include "board.h"
#include "htime.h"
#include "ec11_api.h"
#include "display.h"

int main(void)
{
    int count = 0;
    BoardInit();
    Htime_Init();
    DisplayInit();

    EC11_PinInit();
    DisplayTest();

    while (1)
    {
        count = EC11_GetCount();
    }
    return count;
}
