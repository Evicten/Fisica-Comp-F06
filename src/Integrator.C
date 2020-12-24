#include "Integrator.h"
#include <vector>
#include <numeric>
#include "Derivator.h"
#include <cmath>

using namespace std;

Integrator::Integrator(double fx0, double fx1, const TF1 &fp) : x0(fx0), x1(fx1), Func1D(&fp) { ; }

void Integrator::Trapezoidal(int n, double &Integrator, double &Error)
{

    double h = (x1 - x0) / (double)n;
    double F = 0.;
    double xi = x0;
    double d = 2.;
    vector<double> d2f;

    Derivator deri(x0, x1, f);

    int i;
    for (i = 0; i < n; ++i)
    {
        F = F + (h / d) * (Eval(xi) + Eval(xi + h));
        double xd2 = (xi + xi + h) / (2.);
        d2f.push_back(deri.Dx2(xd2));
        xi += h;
    }
    double sumAvg = accumulate(d2f.begin(), d2f.end(), 0.0);
    Integrator = F;
    double err = h * h * (x1 - x0) / (-12.);
    Error = err * (sumAvg / (double)i);

    d2f.clear();
}

void Integrator::TrapezoidalAdaptative(double &Integrator, double &Error)
{ //Error is input ig

    double d = 2.;
    double xi = x0;
    double F = (Eval(xi) + Eval(x1)) / d; //F1
    double sum = 0.;
    int limsup = 1;
    double limden = (x1 - x0) / d;

    for (int k = 2; k < 1000; ++k)
    { //1000 is enough?
        for (int i = 1; i < limsup + 1; i++)
        {
            double a = (double)(2 * i - 1);
            sum = sum + Eval(x0 + a * limden);
        }
        sum = limden * sum;
        double Fa = F;
        F = F / d + sum;
        if (fabs(F - Fa) < Error)
            break;

        //cout << "ĩteracao k: " << k << endl;

        limsup = limsup * 2;
        limden = limden / d;
    }

    Integrator = F;
}

void Integrator::Simpson(int n, double &Integrator, double &Error)
{
    int m = n;
    double h = (x1 - x0) / (double)n;
    double xi = x0 + h;
    double d = 4.;

    double errorSum = 0.;
    double d4f = 0.;
    double h4 = h * h * h * h;
    double F = 0.;
    vector<double> error;

    if (n % 2 == 1)
        n = n - 1;

    for (int i = 1; i < n; i = i + 2)
    {
        F += Eval(xi - h) + d * Eval(xi) + Eval(xi + h);
        errorSum = Eval(xi - h - h) - 4 * Eval(xi - h) + 6 * Eval(xi) - 4 * Eval(xi + h) + Eval(xi + h + h);
        d4f = errorSum / h4;
        error.push_back(d4f);
        F *= (h / 3.);
        xi = xi + h + h;
    }
    if (m % 2 == 1)
        F += h / 12 * ((-1.) * Eval(xi - h - h) + 8 * Eval(xi - h) + 5 * Eval(xi));
    Integrator = F;

    double sumAvg = accumulate(error.begin(), error.end(), 0.0);
    Error = sumAvg / (double)error.size();

    error.clear();
}

void Integrator::Romberg(int n, double &Integrator, double &Error)
{
    double **mat = new double *[n];
    for (int i = 0; i < n; i++)
        mat[i] = new double[n];
    double erro;
    double q = 4.;

    for (int i = 0; i < n; i++)
        Trapezoidal(i + 1, mat[i][0], erro);

    for (int k = 1; k < n; k++)
    {
        for (int j = k; j < n; j++)
            mat[j][k] = mat[j][k - 1] + (1. / (q - 1.)) * (mat[j][k - 1] - mat[j - 1][k - 1]);

        q *= q;
    }
    int m = n - 1;
    Integrator = mat[m][m];

    for (int i = 0; i < n; i++)
        delete[] mat[i];

    delete[] mat;
}
