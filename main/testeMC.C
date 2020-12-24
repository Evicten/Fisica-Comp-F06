#include "IntegratorMC.h"
#include <iostream>
#include "TRandom.h"
#include "TMath.h"
#include <cmath>

using namespace std;

int main()
{
    double xlow = -50.;
    double xup = 50.;

    auto g = [](double *x, double *par) {
        return 1. / sqrt(2 * TMath::Pi()) * exp(-0.5 * x[0] * x[0]);
    };

    TF1 G("G", g, xlow, xup, 0);
    G.SetNpx(1000);

    auto p = [xup, xlow](double *x, double *par) { //pdf
        return 1. / (xup - xlow);
    };

    TF1 P("P", p, xlow, xup, 0);
    P.SetNpx(1000);

    auto pi = [xlow, xup](double *x, double *par) { //x(y)
        return xlow + x[0] * (xup - xlow);
    };

    TF1 PI("PI", pi, xlow, xup, 0);
    PI.SetNpx(1000);

    IntegratorMC Func(&G);

    double result = 0.;
    double error = 0.;
    int n = 100000;

    Func.IntegralMCIS(n, result, error, &P, &PI);

    cout << "valor res: " << result << " valor erro: " << error << endl;

    cout << "root: " << G.Integral(xlow, xup) << endl;

    /* double k = atan(20.) - atan(-20.);
    cout << "valor k: " << k << endl;


    auto h = [k](double *x, double *par) {
        return tan(x[0] / k - atan(-20.));
    };

    auto pf = [](double *x, double *par) {
        return 1. / (x[0] * x[0] + 1);
    };

    //TF1 A("h", &g, -20., 20., 0);

    TF1 pdf("h", &pf, -20., 20., 0);
    TF1 xy("h", &h, -20., 20., 0);

    gRandom->SetSeed(0);*/

    auto f2 = [](double *x, double *par) {
        double f1 = x[0] * x[0] + x[1] * x[1];
        return (x[0] * x[0] - x[1] * x[1]) / (f1 * f1);
    };

    TF2 B("h", &f2, 0, 0, 1, 1, 0);

    IntegratorMC Func2D(&B);

    double xmin, xmax;

    //A.GetRange(xmin, xmax);

    //cout << "xmin: " << xmin << "  xmax: " << xmax << endl;

    double res;
    int nn = 100000;
    //Func.IntegralMC(1000000, res, error);
    //Func.IntegralMCAR(1000, res, error);
    //Func.IntegralMCIS(n, res, error, &pdf, &xy);
    Func2D.IntegralMCBF(nn, res);

    cout << "valor integral: " << res << endl;

    return 1;
}