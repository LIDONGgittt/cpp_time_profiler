#define USE_PROFILER 1
#include "time_profiler.h"

// Example function.
double function()
{
    double c = 1.2e24;
    PROFILER_HOOK();
    for (int x = 0; x < 1e8; ++x)
        c /= 1.1;
    PROFILER_HOOK();
    return c;
}

// Example program that shows how to use speedo.
int main()
{
    double a = 1.2345;
    PROFILER_HOOK();
    for (int j = 0; j < 200; j++)
        for (long int i = 0; i < 10000; ++i)
        {
            PROFILER_HOOK();
            a *= 9.8765;
        }

    for (long int i = 0; i < 10000; ++i)
        a *= 9.8765;
    PROFILER_HOOK();

    function();
    PROFILER_HOOK();

    return EXIT_SUCCESS;
}
