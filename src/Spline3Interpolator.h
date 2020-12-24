#ifndef __Spline3Interpolator__
#define __Spline3Interpolator__

#include "DataPoints.h"
#include "TF1.h"
#include "TGraph.h"

class Spline3Interpolator : public DataPoints{

    public:
    Spline3Interpolator(int N = 0, double *x = nullptr, double *y = nullptr);
    ~Spline3Interpolator();

    double Interpolate(double);
    TF1* GetInterpolateFunction();
    TGraph* GetGraph();


    private:
    void SetCurvatureLine();
    double fInterpolator(double *fx, double *par){
        return Interpolate(fx[0]);
    }
    TF1* FInterpolator;
    TF1* F0;
    double* K; //2nd Derivatives

};

#endif
