#ifndef __NewtonInterpolator__
#define __NewtonInterpolator__

#include "TF1.h"
#include "DataPoints.h"

class NewtonInterpolator : public DataPoints
{
public:
    NewtonInterpolator(int N = 0, double *x = nullptr, double *y = nullptr); // N, x, y
    ~NewtonInterpolator();

    double Interpolate(double);

    TF1 *GetInterpolateFunction();
    TGraph *GetGraph();

private:
    double fInterpolator(double *fx, double *par)
    {
        return Interpolate(fx[0]);
    }
    TF1 *FInterpolator;
    TF1 *F0;
};
#endif