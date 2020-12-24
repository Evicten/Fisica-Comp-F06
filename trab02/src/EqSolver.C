#include "EqSolver.h"
#include "FCmatrixAlgorithms.h"
#include <cmath>

using namespace std;

EqSolver::EqSolver()
{
    M = new FCmatrixFull();
}

EqSolver::EqSolver(FCmatrix &A, Vec &v)
{
    M = new FCmatrixFull(A);
    b = v;
}

EqSolver::~EqSolver()
{
    delete M;
}

Vec EqSolver::GaussEliminationSolver(int flag)
{

    int m = M->GetRowN() - 1;
    int n = M->GetColN();

    FCmatrixAlgorithms::GaussElimination(M[0], b, flag); //condições

    double *x = new double[m + 1];

    x[m] = b[m] / M[0][m][m];

    for (int k = m - 1; k >= 0; k--)
    {
        double sum = 0.;
        for (int j = k + 1; j < n; j++)
            sum = sum + x[j] * M[0][k][j];

        x[k] = (b[k] - sum) / M[0][k][k];
    }

    Vec res(m + 1, x);
    return res;
}



Vec EqSolver::LUDecompositionSolver(int flag)
{

    int m = M->GetRowN();
    int n = M->GetColN();

    FCmatrixAlgorithms::LUDecomposition(M[0], flag); //condições

    double *x = new double[m];
    double *y = new double[m];

    for (int k = 0; k < n; k++)
    {
        cout << " : " << k << " : ";
        double sum = 0.;
        for (int j = 0; j < n; j++)
            sum = sum + y[j] * M[0][k][j];

        y[k] = (b[k] - sum);
        //cout << "valor de x: " << x[k] << " : ";
    }

    for (int k = m - 1; k >= 0; k--)
    {
        double sum = 0.;
        for (int i = k + 1; i < n; i++)
            sum = sum + x[i] * M[0][k][i];

        x[k] = (y[k] - sum) / M[0][k][k];
    }

    Vec res(m, x);
    return res;
}

void EqSolver::Print()
{
    for (int i = 0; i < M[0].GetRowN(); ++i)
    {
        for (int j = 0; j < M[0].GetColN(); ++j)
            cout << M[0][i][j] << " ";
        cout << endl;
    }

    cout << "_--------vetor eqsolver ------" << endl;
    cout << b << endl;
}

void EqSolver::SetConstants(Vec &a)
{ //condições blabla
    b = a;
}

void EqSolver::SetMatrix(FCmatrix &mat)
{ //condições blabla
    int m = mat.GetRowN();
    vector<Vec> Res;
    for (int i = 0; i < m; ++i)
        Res.push_back(mat[i]);

    M[0].Setvector(Res);
}

Vec EqSolver::JacobiIter()
{

    int m = M[0].GetRowN();
    Vec x(m);
    Vec x_aux(m);
    int it = 0;
    double eps = 1.E-4;
    bool bol = false;
    while (!bol && (it++ < 1000))
    {
        x_aux = x;
        for (int i = 0; i < m; i++)
        {
            x[i] = 0.;
            for (int j = 0; j < m; j++)
            {
                if (i != j)
                    x[i] = x[i] - M[0][i][j] * x_aux[j];
            }
            x[i] = x[i] + b[i];
            x[i] = x[i] / M[0][i][i];

            if (fabs(x[i] - x_aux[i]) < eps)
                bol = true;
            else
                bol = false;
        }
    }
    return x;
}
