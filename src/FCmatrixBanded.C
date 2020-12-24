#include "FCmatrixBanded.h"
#include <iostream>
#include "FCmatrixAlgorithms.h"
#include <algorithm>

using namespace std;

FCmatrixBanded::FCmatrixBanded() : FCmatrix() { ; }

FCmatrixBanded::FCmatrixBanded(double **mat, int d) : FCmatrix(mat, 3, d) {}

FCmatrixBanded::FCmatrixBanded(vector<Vec> &v) : FCmatrix(v) { ; }

FCmatrixBanded::FCmatrixBanded(FCmatrix &v) : FCmatrix(v) {cout << "FCmatrix Banded" << endl;}

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

Vec &FCmatrixBanded::operator[](int i) //vai buscar od Vecs...
{

    return M[i];
}
//methods

int FCmatrixBanded::GetRowN()
{
    return M[1].size();
}

int FCmatrixBanded::GetColN()
{ //redundante mas prontos
    return M[1].size();
}

void FCmatrixBanded::operator=(FCmatrix &mat)
{

    int d1;
    d1 = mat.GetRowN();

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < d1; ++j)
            M[i][j] = mat[i][j];
    };
}

FCmatrixBanded FCmatrixBanded::operator+(FCmatrix &mat)
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

FCmatrixBanded FCmatrixBanded::operator-(FCmatrix &mat)
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

FCmatrixBanded FCmatrixBanded::operator*(FCmatrix &mat)
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

Vec FCmatrixBanded::operator*(Vec &v)
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

    Vec R(Res);
    return R;
}

Vec FCmatrixBanded::GetRow(int j) //useless I think
{
    /* int n = GetColN();
    double *v = new double[n];
    for (int i = 0; i < n; ++i)
        v[i] = M[j][i];

    Vec A(n, v);
    return A;

    delete[] v;*/

    Vec A;

    return A;
}

int FCmatrixBanded::GetRowMax(int j) //useless ig
{
    /*int n = GetColN();
    double *v = new double[n];
    vector<double> h(n);
    for (int i = 0; i < n; ++i)
    {
        h[i] = M[j][i];
        cout << "valor h[i] " << h[i] << endl;
    }

    vector<double>::iterator maxi;
    maxi = max_element(h.begin(), h.end());

    return distance(h.begin(), maxi);*/
    return 0;
}

int FCmatrixBanded::GetColMax(int j)
{ //j coluna a começar em 0
    /* int n = GetColN();
    int m = GetRowN();
     condição j maior ou igual a 1
    if (j > n - 1)
    {
        cout << "erro escolha j menor" << endl;
        exit(1);
    }
    vector<double> line(m);
    vector<double>::iterator maxi;
    for (int i = 0; i < m; ++i)
    {
        line[i] = M[i][j];
        cout << "valor. " << line[i] << "  " << endl;
    }

    maxi = max_element(line.begin(), line.end());
    return distance(line.begin(), maxi);*/
    return 0;
}

void FCmatrixBanded::SetRowIdx(int i, int j) //valor a meter na linha i o valor j //useless
{

    /* int l = GetRowN();
    if (i > l || j > l)
    {
        cout << "linhas inexistentes" << endl;
        exit(1);
    }*/
    //rowindices[i] = j;
}

void FCmatrixBanded::IdxPrint()
{
    /* for (int i = 0; i < GetRowN(); ++i)
        cout << "r[" << i<< "]" << rowindices[i];*/
    //cout << endl;
}

int FCmatrixBanded::GetRowIdx(int i)
{
    //return rowindices[i];
    return 1;
}

void FCmatrixBanded::Setvector(vector<Vec> &mat) //useless
{
    /*  int m = GetRowN();
    for (int i = 0; i < m; ++i)
        M[i] = mat[i];*/
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