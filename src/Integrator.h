#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"
#include "Derivator.h"

class Integrator : public Func1D
{

protected:
    double x0;
    double x1;

public:
    Integrator(double fx0 = 0., double fx1 = 1., const TF1 *fp = nullptr) : x0(fx0), x1(fx1), Func1D(fp) { ; }

    Integrator(double, double, const TF1&); //x0, x1, function

    void Trapezoidal(int, double &, double &); //n, Integral, error
    void TrapezoidalAdaptative(double&, double&); //Integral, error
    void Simpson(int, double&, double&); //n, Integral, Error -------> Rever
    void Romberg(int, double&, double&); //n, Integral -> gives the best value

};

#endif