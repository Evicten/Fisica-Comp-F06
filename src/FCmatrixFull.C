#include "FCmatrixFull.h"
#include <algorithm>
#include "FCmatrixAlgorithms.h"
#include "FCmatrix.h"

using namespace std;

FCmatrixFull::FCmatrixFull() : FCmatrix::FCmatrix()
{
    int n = FCmatrixFull::GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

FCmatrixFull::FCmatrixFull(double **fM, int fm, int fn) : FCmatrix::FCmatrix(fM, fm, fn)
{
    int n = FCmatrixFull::GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

FCmatrixFull::FCmatrixFull(double *fM, int fm, int fn) : FCmatrix(fM, fm, fn)
{
    int n = GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

FCmatrixFull::FCmatrixFull(vector<Vec> &v) : FCmatrix(v)
{
    int n = GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

FCmatrixFull::FCmatrixFull(FCmatrixFull &mat) : FCmatrix(mat)
{ //copy constructor
    classname = mat.classname;
    int n = mat.GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

FCmatrixFull::FCmatrixFull(FCmatrix &mat) : FCmatrix(mat)
{
    int n = mat.GetColN();
    rowindices = new int[n];
    for (int i = 0; i < n; ++i)
        rowindices[i] = i;
}

Vec &FCmatrixFull::operator[](int i)
{
    return M[i];
}

FCmatrixFull FCmatrixFull::operator+(FCmatrix &mat)
{

    int m1, m2, n1, n2;
    m1 = GetRowN();
    m2 = mat.GetRowN();
    n1 = GetColN();
    n2 = mat.GetRowN();

    if (m1 != m2 || n1 != n2)
    {
        cout << "erro na soma das matrizes" << endl;
        exit(1);
    }
    vector<Vec> res;
    for (int i = 0; i < m1; ++i)
    {
        for (int j = 0; j < n1; ++j)
            res[i][j] = mat[i][j] + M[i][j];
    }

    FCmatrixFull Res(res);

    return Res;
}

FCmatrixFull FCmatrixFull::operator-(FCmatrix &mat)
{

    int m1, m2, n1, n2;
    m1 = GetRowN();
    m2 = mat.GetRowN();
    n1 = GetColN();
    n2 = mat.GetRowN();

    if (m1 != m2 || n1 != n2)
    {
        cout << "erro na soma das matrizes" << endl;
        exit(1);
    }
    vector<Vec> res;
    for (int i = 0; i < m1; ++i)
    {
        for (int j = 0; j < n1; ++j)
            res[i][j] = M[i][j] - mat[i][j];
    }

    FCmatrixFull Res(res);

    return Res;
}

FCmatrixFull FCmatrixFull::operator*(double lambda)
{

    int m1, n1;
    m1 = GetRowN();
    n1 = GetColN();

    vector<Vec> res;

    for (int i = 0; i < m1; ++i)
    {
        for (int j = 0; j < n1; ++j)
            res[i][j] = lambda * M[i][j];
    }

    FCmatrixFull Res(res);

    return Res;
}

FCmatrixFull FCmatrixFull::operator*(FCmatrix &mat)
{ //M*mat&

    int m1, m2, n1, n2;
    m1 = GetRowN();
    m2 = mat.GetRowN();
    n1 = GetColN();
    n2 = mat.GetRowN();

    double sum = 0.;

    if (n1 != m2)
    {
        cout << "erro na na dimensão das matrizes para o produto" << endl;
        exit(1);
    }

    vector<Vec> rest;

    for (int i = 0; i < m1; ++i)
    {

        for (int j = 0; j < n2; ++j)
        {
            sum = 0.;

            for (int k = 0; k < m2; ++k)
                sum = sum + mat[i][k] * M[k][j];

            rest[i][j] = sum;
        }
    }

    FCmatrixFull Res(rest);

    return Res;
}

Vec FCmatrixFull::operator*(Vec &v)
{
    int l = v.size();
    int m, n;
    m = GetRowN();
    n = GetColN();

    if (l != n)
    {
        cout << "erro nas dimensões da matriz e vetor" << endl;
        exit(1);
    }

    Vec Res;
    double sum = 0.;

    for (int i = 0; i < m; ++i)
    {
        for (int k = 0; k < n; ++k)
            sum = sum + M[i][k] * v[k];

        Res[i] = sum;
        sum = 0.;
    }

    Vec R(Res);
    return R;
}


Vec FCmatrixFull::GetRow(int j)
{
    int n = GetColN();
    double *v = new double[n];
    for (int i = 0; i < n; ++i)
        v[i] = M[j][i];

    Vec A(n, v);
    return A;

    delete[] v;
}

void FCmatrixFull::Print()
{
    int iR;
    cout << "matriz: " << classname << endl;
    for (int i = 0; i < M.size(); ++i)
    {
        for (int j = 0; j < M[i].size(); ++j)
        {
            iR = GetRowIdx(i);
            cout << M[iR][j] << " ";
        }
        cout << endl;
    }
}

int FCmatrixFull::GetRowMax(int j)
{
    int n = GetColN();
    double *v = new double[n];
    vector<double> h(n);
    for (int i = 0; i < n; ++i)
    {
        h[i] = M[j][i];
        cout << "valor h[i] " << h[i] << endl;
    }

    vector<double>::iterator maxi;
    maxi = max_element(h.begin(), h.end());

    return distance(h.begin(), maxi);
}

int FCmatrixFull::GetColMax(int j)
{ //j coluna a começar em 0
    int n = GetColN();
    int m = GetRowN();
    // condição j maior ou igual a 1
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
    return distance(line.begin(), maxi);
}

void FCmatrixFull::SetRowIdx(int i, int j) //valor a meter na linha i o valor j
{

    int l = GetRowN();
    if (i > l || j > l)
    {
        cout << "linhas inexistentes" << endl;
        exit(1);
    }
    rowindices[i] = j;
}

void FCmatrixFull::IdxPrint(){
    for (int i = 0; i < GetRowN(); ++i)
        cout << "r[" << i<< "]" << rowindices[i];
    cout << endl;
}

int FCmatrixFull::GetRowIdx(int i)
{
    return rowindices[i];
}

void FCmatrixFull::Setvector(vector<Vec> &mat)
{
    int m = GetRowN();
    for (int i = 0; i < m; ++i)
        M[i] = mat[i];
}

double FCmatrixFull::Determinant()
{
    int m = GetRowN();
    int n = GetColN();
    Vec A(m);
    cout << "Determinante" << endl;
    if (m != n)
    {
        cout << "matrix não quadrada" << endl;
        exit(1);
    }
    FCmatrixAlgorithms::GaussElimination(*this, A, 1);
    int iR;
    double lam = 1.;
    for (int i = 0; i < m; ++i){
        iR = GetRowIdx(i);
        lam = lam * M[iR][i];
    }
    return lam;
}
