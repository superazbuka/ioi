#include "grader.h"


void Solve()
{
    int t[] = {0, 1, 1, 1};
    int k = 200;
    while (k != 0)
    {
        k = Theory(t[1], t[2], t[3]);
        t[k]++;
    }
}

