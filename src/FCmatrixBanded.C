#include "FCmatrixBanded.h"
#include <iostream>
#include "FCmatrixAlgorithms.h"
#include <algorithm>

using namespace std;

FCmatrixBanded::FCmatrixBanded() : FCmatrix() { ; }

FCmatrixBanded::FCmatrixBanded(double **mat, int d) : FCmatrix(mat, 3, d) { ; }

FCmatrixBanded::FCmatrixBanded(const vector<Vec> &v) : FCmatrix(v) { ; }

FCmatrixBanded::FCmatrixBanded(const FCmatrix &v) : FCmatrix(v) { cout << __PRETTY_FUNCTION__ << endl; }

void FCmatrixBanded::Print()
{ //a - linha 0  below diag| b - linha 1 diagonal| c - linha 2 up diag
    int l = M[1].size();
    for (int i = 0; i < l; ++i)
    {
        if (i == 0)
        {
            cout << M[1][i] << " " << M[2][i] << " ";
        }
        if (i >= 2)
        {
            for (int j = 0; j < i - 1; j++)
                cout << "0 ";
        }
        if (i > 0 && i < l - 1)
        {
            cout << M[0][i - 1] << " " << M[1][i] << " " << M[2][i] << " ";
        }
        for (int p = i + 1; p < l - 1; ++p)
            cout << "0 ";
        if (i == l - 1)
            cout << M[0][i - 1] << " " << M[1][i];
        cout << endl;
    }
}

//operators--------------------------------------------
Vec &FCmatrixBanded::operator[](int i) //vai buscar od Vecs...
{
    return M[i];
}

void FCmatrixBanded::operator=(FCmatrixBanded &mat)
{

    int d1;
    d1 = mat.GetRowN();

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < d1; ++j)
            M[i][j] = mat[i][j];
    };
}

FCmatrixBanded FCmatrixBanded::operator+(FCmatrixBanded &mat)
{

    int d1, d2;
    d1 = GetRowN();
    d2 = mat.GetRowN();

    if (d1 != d2)
    {
        cout << "erro na soma das matrizes dimensões matrizes" << endl;
        exit(1);
    }
    vector<Vec> res;
    double *line = new double[d1];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < d1; ++j)
            line[j] = mat[i][j] + M[i][j];

        Vec A(d1, line);
        res.push_back(A);
    }

    delete[] line;

    FCmatrixBanded Res(res);

    return Res;
}

FCmatrixBanded FCmatrixBanded::operator-(FCmatrixBanded &mat)
{

    int d1, d2;
    d1 = GetRowN();
    d2 = mat.GetRowN();

    if (d1 != d2)
    {
        cout << "erro na soma das matrizes dimensões matrizes" << endl;
        exit(1);
    }
    vector<Vec> res;
    double *line = new double[d1];

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < d1; ++j)
            line[j] = mat[i][j] - M[i][j];

        Vec A(d1, line);
        res.push_back(A);
    }

    delete[] line;

    FCmatrixBanded Res(res);

    return Res;
}

FCmatrixBanded FCmatrixBanded::operator*(double lambda)
{

    int d1;
    d1 = GetRowN();

    double *line = new double[d1];
    vector<Vec> res;

    for (int i = 0; i < 3; ++i)
    {
        cout << "valor i: " << i << endl;
        for (int j = 0; j < d1; ++j)
        {
            line[j] = lambda * M[i][j];
            cout << "valor j: " << j << endl;
        }
        Vec A(d1, line);
        res.push_back(A);
    }
    delete[] line;
    FCmatrixBanded Res(res);

    return Res;
}

FCmatrixBanded FCmatrixBanded::operator*(FCmatrixBanded &mat)
{ //M*mat&
    // think about it, its not easy at all!! é uma mess e sai da matrix tridiagonal, vou ignorar agora...
    int d1, d2;
    d1 = GetRowN();
    d2 = mat.GetRowN();

    if (d1 != d2)
    {
        cout << "erro no produto na dimensão das  matrizes" << endl;
        exit(1);
    }
    vector<Vec> res;
    double *line = new double[d1];
    double sum = 0.;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < d1; ++j)
        {
            if (i == 1)
            {
                if (j > 0 && j < d1 - 1)
                    res[i][j] = M[0][0];
            }
            for (int k = 0; k < d1; ++k)
                sum = sum + M[i][k] * M[k][j];

            Vec A(d1, line);
            res.push_back(A);
        }
    }

    delete[] line;

    FCmatrixBanded Res(res);

    return Res;
}

Vec FCmatrixBanded::operator*(const Vec &v)
{
    int l = v.size();
    int d;
    d = GetRowN();

    if (d != l)
    {
        cout << "erro nas dimensões da matriz e vetor" << endl;
        exit(1);
    }

    Vec Res(d);
    double sum = 0.;

    for (int i = 0; i < d; ++i)
    {
        if (i == 0)
            sum = M[1][i] * v[i] + M[2][i] * v[1];

        if (i > 0 && i < d - 1)
            sum = M[0][i - 1] * v[i - 1] + M[1][i] * v[i] + M[2][i] * v[i];
        if (i == d - 1)
            sum = M[1][i] * v[i] + M[0][i - 1] * v[i - 1];

        Res[i] = sum;
        sum = 0.;
    }
    return Res;
}

double FCmatrixBanded::Determinant()
{
    int d = GetRowN();
    Vec A(d);
    cout << "--------Determinante------------" << endl;

    FCmatrixAlgorithms::GaussSolverBanded(*this, A, 0);
    double lam = 1.;
    for (int i = 0; i < d; ++i)
        lam = lam * M[1][i];

    return lam;
}

int FCmatrixBanded::GetRowN()
{
    return M[1].size();
}

int FCmatrixBanded::GetColN()
{ //redundante mas prontos
    return M[1].size();
}