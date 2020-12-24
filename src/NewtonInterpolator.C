#include "NewtonInterpolator.h"
#include <iostream>

using namespace std;

NewtonInterpolator::NewtonInterpolator(int N, double *x, double *y) : DataPoints(N, x, y)
{
    FInterpolator = new TF1("FInterpolator", this, &NewtonInterpolator::fInterpolator, 0.1, 5.1, 0, "NewtonInterpolator", "fInterpolator");
    DataPoints::Print();
    F0 = nullptr;
}

NewtonInterpolator::~NewtonInterpolator() {;}

double NewtonInterpolator::Interpolate(double x0)
{

    double *yp = new double[N];

    for (int i = 0; i < N; ++i)
        yp[i] = y[i];
    double P;

    for (int k = 1; k < N; ++k)
    { //expoente
        for (int i = k; i < N; ++i)
        { //indice
            yp[i] = (yp[i] - yp[k - 1]) / (x[i] - x[k - 1]);
        }
    }
    int n = N - 1;
    P = yp[n];
    for (int j = 1; j < N; ++j)
        P = yp[n - j] + (x0 - x[n - j]) * P;

    delete [] yp;

    return P;
}

TGraph* NewtonInterpolator::GetGraph()
{
    TGraph *A = new TGraph(FInterpolator);
    return A;
}

TF1* NewtonInterpolator::GetInterpolateFunction(){
    return FInterpolator;
}