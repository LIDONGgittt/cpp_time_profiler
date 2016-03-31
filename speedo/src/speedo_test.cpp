#define PROFILE 1
#include "speedo/speedo.h"


// Example function.
void function()
{
___ for (int x = 0; x < 1e9; x++)
        ;
___
}

// Example program that shows how to use speedo.
int main()
{
___ for (int j = 0; j < 20; j++)
___    for (long int i = 0; i < 10000000; ++i)
            ;
___
    for (long int i = 0; i < 10000000; ++i)
        ;

    function();
___
    return 0;
}
