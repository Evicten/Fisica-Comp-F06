#include "Vandermonde.h"
#include <algorithm>
#include "EqSolver.h"
#include <vector>
#include <iostream>
#include "TAxis.h"
#include <cmath>
#include "FCmatrixAlgorithms.h"

using namespace std;

Vandermonde::Vandermonde() : x(nullptr), y(nullptr), fPoly(nullptr) { ; }

Vandermonde::Vandermonde(unsigned N, double xMin, double xMax, const TF1 &A) : n(N), x(new double[N]), y(new double[n])
{
    double dx = (xMax - xMin) / (n - 1);

    x[0] = xMin;
    double xi = xMin;
//iterar sovbre pontos para determinar n pontos da funcao dada
    for (int i = 0; i < n; ++i)
    {
        x[i] = xi;
        y[i] = A.Eval(xi);
        xi += dx;
    }

    calculateCoeffs(); //Resolver o sistema da matriz de Vandermonde Cx = y

    SetPolynomialFunction(); //Definir o polinomio de interpolacao
    SetGraphicsPoints(); 
}

Vandermonde::~Vandermonde() //destrutor
{

    if (x)
        delete[] x;
    if (y)
        delete[] y;

    if (fPoly)
        delete fPoly;
}

void Vandermonde::calculateCoeffs() //calculo dos coeficientes
{
    double **mat = new double *[n];
    for (int i = 0; i < n; i++)
        mat[i] = new double[n];

    for (int i = 0; i < n; i++)
    {
        mat[i][0] = 1.;
        for (int k = 1; k < n; k++)
            mat[i][k] = mat[i][k - 1] * x[i];
    }

    FCmatrixFull A(mat, n, n);
    MatrixCoefs = A;

    Vec v(n, y);
    EqSolver Elim(MatrixCoefs, v);

    PolCoefs = Elim.GaussEliminationSolver(0); //doing Gauss elimination on MatrixCoefs

    for (int i = 0; i < n; ++i)
        delete[] mat[i];

    delete[] mat; //limpar memória heap
}

double Vandermonde::Interpolate(double x0)
{

    double *x_aux = new double[n];
    x_aux[0] = 1.;
    for (int i = 1; i < n; ++i)
        x_aux[i] = x_aux[i - 1] * x0;

    double sum = 0.;
    for (int i = 0; i < n; ++i)
        sum += x_aux[i] * PolCoefs[i];

    delete[] x_aux;

    return sum;
}

double Vandermonde::GetCoefError() 
{

    Vec b(n, y);
    Vec D = MatrixCoefs * PolCoefs;
    D = D - b;

    //double *v = new double[n];
    vector<double> h(n);
    for (int i = 0; i < n; ++i)
        h[i] = fabs(D[i]);

    vector<double>::iterator maxi; //calculo do valor maximo de |dE|
    maxi = max_element(h.begin(), h.end());

    return *maxi;
}

void Vandermonde::GetInverseMatrix(FCmatrixFull &mat1)
{
    FCmatrixFull A;
    FCmatrixAlgorithms::Inverse(MatrixCoefs, A);
    mat1 = A;
}

const Vec &Vandermonde::GetCoefficients()
{
    return PolCoefs;
}

const FCmatrixFull &Vandermonde::GetMatrix()
{
    return MatrixCoefs;
}

const double *Vandermonde::GetX()
{
    return x;
}

const double *Vandermonde::GetY()
{
    return y;
}

TF1 &Vandermonde::GetPolyFunc()
{
    return *fPoly;
}

TGraph &Vandermonde::GetGraphPoints()
{
    return gPoints;
}

void Vandermonde::SetGraphicsPoints()
{
    gPoints = TGraph(n, x, y);
    gPoints.SetMarkerStyle(20);
    gPoints.SetMarkerColor(38);
    gPoints.SetMarkerSize(2);
    gPoints.GetXaxis()->SetRangeUser(0.9 * x[0], 1.1 * x[n - 1]);
    gPoints.SetNameTitle("Points Graphic");
}

void Vandermonde::SetPolynomialFunction()
{
    fPoly = new TF1("fPoly", this, &Vandermonde::fInterpolator, x[0], x[n - 1], 0, "VandermondeInterpolator", "fInterpolator");
    fPoly->SetLineColor(kRed + 2);
    fPoly->SetLineWidth(2);
    fPoly->SetLineStyle(kSolid);
}
