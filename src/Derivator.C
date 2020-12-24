#include "Derivator.h"
#include <iostream>

using namespace std;


double Derivator::Dx1(double xval){ //central difference
    
    double h = 1e-5;
    double d = 2.;

    return (Eval(xval + h) - Eval(xval - h))/(2*h);
}


double Derivator::Dx2(double xval){

    double h = 1e-5;
    double d = 2.;

    return (Eval(xval + h) - d*Eval(xval) + Eval(xval - h))/(h*h);
}
