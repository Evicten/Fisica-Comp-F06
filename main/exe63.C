#include "FCrand.h"
#include <iostream>

using namespace std;

int main()
{

    FCrand A(100);
    FCrand B(5);

    long int N = 1000000;

    float *x = A.GetRandom(N, 0., 1.);
    float *y = B.GetRandom(N, 0., 1.);

    int n = 0;
    float resi;

    for (int i = 0; i < N; i++)
    {
        resi = x[i] * x[i] + y[i] * y[i];
        if (resi < 1.)
            n = n + 1;
    }


    float pi = 4.*(float)n / ((float)N);

    cout << "valor de pi: " << pi << endl;

    return 1;
}