#include "LagrangeInterpolator.h"
#include "NevilleInterpolator.h"
#include "NewtonInterpolator.h"
#include "Spline3Interpolator.h"
#include <iostream>
#include "TCanvas.h"
using namespace std;

int main(){

    double* x = new double[6];
    x[0] = 1.; x[1]= 2.; x[2] = 3.; x[3] = 4.; x[4] = 5.; x[5] = 6.;

    double* y(new double[6]);
    y[0] = 0.; y[1] = 1.; y[2] = 0.; y[3] = 1.; y[4] = 0.; y[5] = 1.;
   
    LagrangeInterpolator A(6, x, y);
    NevilleInterpolator B(5, x, y);
    NewtonInterpolator C(5, x, y);

    cout << "auiq" << endl;
    Spline3Interpolator D(5, x, y);

    cout << "here" << endl;



    cout << "valor Lag " << A.Interpolate(2.1) << endl;
    cout << "valor Nev " << B.Interpolate(2.1) << endl;
    cout << "valor New " << C.Interpolate(2.1) << endl;

    cout << "here3332" << endl;
    
    cout << "valor Spline3 " << D.Interpolate(2.1) << endl;



    /*TCanvas *c1 = new TCanvas("c1", "Interpolation", 200, 10, 500, 300);
    TGraph* a = A.GetGraph();
    a->Draw("AC*");*/


    return 1;
}