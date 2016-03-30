#include "speedo/speedo.h"
#define PROFILE 1


// Example program that shows how to use speedo.
int main()
{
___ for (int j = 0; j < 20; j++)
       for (long int i = 0; i < 10000000; ++i)
            ;
___
    for (long int i = 0; i < 10000000; ++i)
        ;
___
    return 0;
}
