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

    double h = (x1 - x0) / (double)n;
    double xi = x0 + h;
    double d = 4.;

    if (n % 2 == 0)
    {
        double F = 0.;
        double errorSum = 0.;
       /* for (int i = 1; i < n; i = i + 2)
        {
            F += Eval(xi - h) + d * Eval(xi) + Eval(xi + h);
            if (i == 1 || i = n - 1)
                //curly brackets
                else //curly brackets
                    errorSum += Eval(xi - h - h) - 4 * Eval(xi - h) + 6 * Eval(xi) - 4 * Eval(xi + h) + Eval(xi + h + h) xi += h + h;
        }
        F *= (h / 3.); //falta erro derivada de ordem 4?
        F += h / 12 * ((-1.) * Eval(xi - h - h) + 8 * Eval(xi - h) + 5 * Eval(xi));
        Integrator = F;

    } //ELSE*/
    }
    double F = 0.;
    for (int i = 1; i < n; i = i + 2)
    {
        F += Eval(xi - h) + d * Eval(xi) + Eval(xi + h);
        xi += h + h;
    }

    Integrator = F * (h / 3.); //falta erro derivada de ordem 4?
}

void Integrator::Romberg(int n, double &Integrator, double &Error)
{
    double **mat = new double *[n];
    for (int i = 0; i < n; i++)
        mat[i] = new double[n];
    double erro;
    double q = 4.;

    for (int i = 0; i < n; i++)
    {
        Trapezoidal(i + 1, mat[i][0], erro);
        //cout << "valor mat0i: " << mat[0][i] << " valor i: " << i << endl;
    }

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
