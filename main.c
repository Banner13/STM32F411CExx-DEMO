#include <stdio.h>
#include <string.h>
#include "board.h"
#include "ec11_api.h"

int main(void)
{
    int count = 0;
    BoardInit();

    EC11_PinInit();

    while (1)
    {
        count = EC11_GetCount();
    }
    return count;
}
