
#include "TF1.h"
#include "NevilleInterpolator.h"
#include "TGraph.h"

NevilleInterpolator::NevilleInterpolator(int N, double *x, double *y) : DataPoints(N, x, y)
{
    FInterpolator = new TF1("FInterpolator", this, &NevilleInterpolator::fInterpolator, -10.1, 10.1, 0, "NevilleInterpolator", "fInterpolator");
    DataPoints::Print();
    F0 = nullptr;
}

NevilleInterpolator::~NevilleInterpolator(){;}

double NevilleInterpolator::Interpolate(double xval)
{
    double *yp = new double[N];
    for (int i = 0; i < N; i++)
    {
        yp[i] = y[i];
    }

    for (int k = 1; k < N; k++)
    {
        for (int i = 0; i < N - k; i++)
        yp[i] = ((xval-x[i+k])*yp[i] - (xval - x[i])*yp[i+1])/(x[i] - x[i+k]);
    }
    double A = yp[0];
    delete[] yp;
    return A;

}

TF1* NevilleInterpolator::GetInterpolateFunction(){
    return FInterpolator;
}

TGraph* NevilleInterpolator::GetGraph(){
    
    TGraph* A = new TGraph(FInterpolator);
    return A;
}
