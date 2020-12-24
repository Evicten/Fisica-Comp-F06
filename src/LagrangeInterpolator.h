
#ifndef __LagrangeInterpolator__
#define __LagrangeInterpolator__

#include "DataPoints.h"
#include "TF1.h"

class LagrangeInterpolator : public DataPoints
{

public:
    LagrangeInterpolator(int N = 0, double *x = nullptr, double *y = nullptr); // N, x, y
    ~LagrangeInterpolator();
    double Interpolate(double);

    TF1 *GetInterpolateFunction();
    TGraph *GetGraph();

    //Prints ? e draws?
private:
    double fInterpolator(double *fx, double *par)
    {
        return Interpolate(fx[0]);
    }
    TF1 *FInterpolator;
    TF1 *F0;
};

#endif
