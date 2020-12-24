#include "ODEpoint.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

ODEpoint::ODEpoint(int fdim, const double *xi) : ndim(fdim), x(new double[fdim + 1])
{

    for (int i = 0; i < fdim + 1; i++)
        x[i] = xi[i];
}

ODEpoint::ODEpoint(const ODEpoint &A) //copy constructor
{
    ndim = A.ndim;
    x = new double[ndim + 1];
    for (int i = 0; i < ndim + 1; i++)
        x[i] = A.x[i];
}

ODEpoint::~ODEpoint()
{
    //cout << __PRETTY_FUNCTION__ << endl;
    if (x)
        delete x;
}

ODEpoint ODEpoint::operator*(double lam) const //no tempo não faz nada
{
    for (int i = 1; i < ndim + 1; i++)
        x[i] = lam * x[i];

    return ODEpoint(ndim, x);
}

ODEpoint ODEpoint::operator+(const ODEpoint &A) const
{

    if (ndim != A.ndim)
    {
        cout << "erro de dimensoes " << endl;
        exit(1);
    }
    for (int i = 1; i < ndim + 1; i++)
        x[i] = x[i] + A.x[i];

    return ODEpoint(ndim, x);
}

ODEpoint ODEpoint::operator-(const ODEpoint &A) const //tempos à parte, nao sao alterados
{
    if (ndim != A.ndim)
    {
        cout << "erro de dimensoes " << endl;
        exit(1);
    }
    for (int i = 1; i < ndim + 1; i++)
        x[i] = x[i] - A.x[i];

    return ODEpoint(ndim, x);
}

const ODEpoint& ODEpoint::operator=(const ODEpoint &A) 
{
    if (this != &A)
    {
        delete x;
        x = new double[A.ndim + 1];
        ndim = A.ndim;

        for (int i = 0; i < ndim + 1; i++)
            x[i] = A.x[i];
    }
    return *this;
}

const double ODEpoint::operator[](int i) const
{
    if (i > (ndim + 1))
    {
        cout << __PRETTY_FUNCTION__ << endl;
        exit(1);
    }
    return x[i];
}

double &ODEpoint::operator[](int i)
{
    if (i > (ndim+1))
    {
        cout << __PRETTY_FUNCTION__ << endl;
        exit(1);
    }
    return x[i];
}


