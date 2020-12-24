#include "LagrangeInterpolator.h"
#include <iostream>

using namespace std;

LagrangeInterpolator::LagrangeInterpolator(int N, double *x, double *y) : DataPoints(N, x, y)
{
    FInterpolator = new TF1("FInterpolator", this, &LagrangeInterpolator::fInterpolator, 0.1, 5.1, 0, "NevilleInterpolator", "fInterpolator");
    DataPoints::Print();
    F0 = nullptr;
}

LagrangeInterpolator::~LagrangeInterpolator(){;}

double LagrangeInterpolator::Interpolate(double x0)
{
    double res = 0.;
    double num = 1.;
    double den = 1.;
    for (int k = 0; k < N; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            if (i == k)
                continue;
            num = num * (x0 - x[i]);
            den = den * (x[k] - x[i]);
        }
        res = res + y[k] * (num / den);
        num = 1.;
        den = 1.;
    }
    return res;
}

TGraph *LagrangeInterpolator::GetGraph()
{
    TGraph *A = new TGraph(FInterpolator);
    return A;
}

TF1* LagrangeInterpolator::GetInterpolateFunction(){
    return FInterpolator;
}