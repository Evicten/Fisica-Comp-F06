#ifndef __NevilleInterpolator__
#define __NevilleInterpolator__

#include "DataPoints.h"
#include "TFile.h"
#include "TF1.h"
#include "TGraph.h"
#include <vector>

class NevilleInterpolator : public DataPoints
{

public:
    NevilleInterpolator(int N = 0, double *x = nullptr, double *y = nullptr);
    ~NevilleInterpolator();

    double Interpolate(double);
    TF1* GetInterpolateFunction();
    TGraph* GetGraph();

private:
    double fInterpolator(double* fx, double* par){
        return Interpolate(fx[0]);
    }
    TF1* FInterpolator;
    TF1* F0;
};

#endif


