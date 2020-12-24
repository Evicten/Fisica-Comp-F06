#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"
#include "TF1.h"

class Derivator : public Func1D{

    public:
    Derivator(double fx0, double fx1,  const TF1* fp) : x0(fx0), x1(fx1), Func1D(fp) {;}
    Derivator(double fx0, double fx1, const TF1& fp) : x0(fx0), x1(fx1), Func1D(fp) {;}
    ~Derivator() = default;


    double Dx1(double);
    double Dx2(double);


    protected:
    double x0;
    double x1;

};

#endif