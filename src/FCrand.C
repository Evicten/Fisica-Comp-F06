#include "FCrand.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

FCrand::FCrand(int sd, int aa, int cc, int mm) : a(aa), c(cc), m(mm)
{
    if (sd == 2)
        seed = time(nullptr);
    else
        seed = sd;
}

float FCrand::GetRandom()
{
    int c = (a * seed + c) % m;
    return (float)c / (float)m;
}

float FCrand::GetRandom(float min, float max)
{
    if((max - min) < 0.1){
        cout << "nao" << endl;
        exit(1);
    }
    return (max - min) * GetRandom() + min;
}

float* FCrand::GetRandom(int N)
{
    if (N < 1)
    {
        cout << "Erro na dimensao do vetor, escolha um int N maior que 1" << endl;
        exit(1);
    }
    float *v = new float[N];
    for(int i = 0; i < N; i++)
    v[i] = GetRandom();

    return v;
}

float* FCrand::GetRandom(int N, float min, float max)
{
    if (N < 1 || (max - min) < 0.1)
    {
        cout << "Erro na dimensao do vetor, escolha um int N maior que 1 ou valores max e min inadequados" << endl;
        exit(1);
    }
    float *v = new float[N];
    for(int i = 0; i < N; i++)
    v[i] = GetRandom(min, max);

    return v;
}

