#define PROFILE 1
#include "speedo/speedo.h"


// Example function.
void function()
{
___ for (int x = 0; x < 1e9; x++)
        double c = 1.2e345 / 9.8e765;
___
}


// Example program that shows how to use speedo.
int main()
{
___ for (int j = 0; j < 20; j++)
        for (long int i = 0; i < 10000000; ++i)
___         double a = 1.2345 * 9.8765;
    
for (long int i = 0; i < 10000000; ++i)
        double b = 1.2345 / 9.8765;
___

    function();
___
    return EXIT_SUCCESS;
}
