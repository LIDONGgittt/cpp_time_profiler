#define PROFILE 1
#include "speedo/speedo.h"


// Example function.
double function()
{
    double c = 1.2e34;
xxx for (int x = 0; x < 1e9; ++x)
        c /= 1.1;
xxx
    return c;
}


// Example program that shows how to use speedo.
int main()
{
    double a = 1.2345;
xxx for (int j = 0; j < 20; j++)
        for (long int i = 0; i < 100000; ++i)
xxx         a *= 9.8765;

    for (long int i = 0; i < 100000; ++i)
        a *= 9.8765;
xxx

    function();
xxx
    return EXIT_SUCCESS;
}
