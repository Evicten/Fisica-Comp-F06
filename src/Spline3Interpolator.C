#include "Spline3Interpolator.h"
#include "FCmatrixBanded.h"
#include "FCmatrixAlgorithms.h"
#include <iostream>

using namespace std;

Spline3Interpolator::Spline3Interpolator(int N, double *x, double *y) : DataPoints(N, x, y)
{
    FInterpolator = new TF1("FInterpolator", this, &Spline3Interpolator::fInterpolator, 1, 5, 0, "Spline3Interpolator", "fInterpolator");
    DataPoints::Print();
    F0 = nullptr;

    K = new double[N - 2];

    SetCurvatureLine();
}

Spline3Interpolator::~Spline3Interpolator()
{
    delete[] K;
}

void Spline3Interpolator::SetCurvatureLine()
{

    int dk, dj, uk, uj;
    dk = 0;
    dj = 2;
    uk = 1;
    uj = 2;
    double vd, vu;
    double **mat = new double *[3];
    for (int i = 0; i < 3; ++i)
        mat[i] = new double[N - 2];

    double *v = new double[N - 1];

    double num1, num2, den1, den2;

    for (int i = 0; i < N - 2; ++i)
    {
        if (dj == N)
            break;

        mat[1][i] = 2 * (x[dk] - x[dj]);
        mat[2][i] = x[uk] - x[uj];
        mat[0][i] = mat[2][i];

        num1 = y[dk] - y[uk];
        den1 = x[dk] - x[uk];

        num2 = y[uk] - y[uj];
        den2 = x[uk] - x[uj];

        v[i] = 6 * (num1 / den1 - num2 / den2);
        cout << "num1 : " << num1 << "num2 : " << num2 << "den1 : " << den1 << "den2 : " << den2 << endl;
        cout << "valor vi: " << v[i] << endl;

        dk = dk + 1;
        dj = dj + 1;
        uk = uk + 1;
        uj = uj + 1;
        num1 = 0.;
        num2 = 0.;
        den1 = 0.;
        den2 = 0.;

        cout << "valor i: " << i << endl;
    }

    Vec vi(N - 2, v);
    FCmatrixBanded R(mat, N - 2);

    R.Print();
    cout << vi << endl;

    Vec res = FCmatrixAlgorithms::GaussSolverBanded(R, vi, 1);

    R.Print();
    cout << res << endl;

    for (int i = 0; i < N - 2; ++i)
    {
        K[i] = res[i];
        cout << "valor k: " << K[i] << endl;
    }

    delete[] v;
    for (int i = 0; i < 3; ++i)
        delete[] mat[i];

    delete[] mat;
}

double Spline3Interpolator::Interpolate(double x0)
{

    int i;
    for (i = 0; i < N; ++i)
    { //upper bound
        cout << "valor i interpolate:  " << i << endl;
        cout << "valor-,m,m: " << x0 - x[i] << endl;
        if ((x0 - x[i]) < 0.)
        {
            break;
        }
    }
    if (i == 0 || i == N) // out of range
        return 0.;

    cout << "valor i: " << i << endl; // i : upper bound
    // erro must below -->>>>>>>>>
    double a = 1. / 6.;
    double res1, res2;
    double xx1 = x0 - x[i];
    double xx2 = x0 - x[i - 1];
    double xix = x[i - 1] - x[i];
    cout << "xx1: " << xx1 << "xx2: " << xx2 << "xix: " << xix << endl;

    double xx13 = xx1 * xx1 * xx1;
    double xx23 = xx2 * xx2 * xx2;
    res1 = a * K[i - 1] * (xx13 / xix - xx1 * xix) - a * K[i] * (xx23 / xix - xx2 * xix);
    res2 = (y[i - 1] * xx1 - y[i] * xx2) / xix;

    cout << "res " << res1 << " , ," << res2 << endl;

    double Res = res1 + res2;
    return Res;
}

TF1 *Spline3Interpolator::GetInterpolateFunction()
{
    return FInterpolator;
}

TGraph *Spline3Interpolator::GetGraph()
{
    TGraph *A = new TGraph(FInterpolator);
    return A;
}
