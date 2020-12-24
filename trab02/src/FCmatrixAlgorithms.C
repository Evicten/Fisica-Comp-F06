#include "FCmatrixAlgorithms.h"
#include <algorithm>
#include <cmath>

using namespace std;

void FCmatrixAlgorithms::Inverse(FCmatrix &A, FCmatrix &Res) //obter a matriz a inversa 
{ //usado o método da Gauss Jordan : A | I ---> A⁻1

    int m = A.GetRowN(); //linhas
    int n = A.GetColN(); //colunas
    if (n != m)
    {
        cout << "erro na dimensão m do sistema - GaussElimination" << endl;
        exit(1);
    }

    vector<Vec> Iaux;

    Vec nul(n);
    for (int i = 0; i < n; i++)
    { //matrix identidade suponho xD
        Iaux.push_back(nul);
        Iaux[i][i] = 1.;
    }

    FCmatrixFull I(Iaux);

    for (int i = 0; i < m; i++)
    {

         if (fabs(A[i][i]) <= 0.00001) //trocar a linha do pivot caso este seja muito pequeno...
        {
            int p;
            for (p = i; fabs(A[p][i]) <= 0.00001; ++p)
            {
                ;
            }
            Swap(A, p, i);
            Swap(I, p, i);
        }

        double l = A[i][i];
        for (int t = 0; t < n; t++)
        {
            A[i][t] = A[i][t] * (1. / l);
            I[i][t] = I[i][t] * (1. / l);
        }

        for (int h = i + 1; h < m; h++) //linha pós pivot
        {

            if (fabs(A[h][i]) <= 0.00001)
                continue;

            double lam = A[h][i] / A[i][i];

            for (int j = i; j < n; j++) //operação na linha
            {
                A[h][j] = A[h][j] - lam * A[i][j];
            }
            for (int j = 0; j < n; j++)
            {
                I[h][j] = I[h][j] - lam * I[i][j];
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {

        for (int h = i - 1; h >= 0; h--) //linha pós pivot
        {

            if (fabs(A[h][i]) <= 0.00001)
                continue;

            double lam = A[h][i] / A[i][i];

            A[h][i] = 0.;
            for (int j = 0; j < n; j++)
                I[h][j] = I[h][j] - lam * I[i][j];

        }
    
    }
    Res = I;
}

void FCmatrixAlgorithms::GaussElimination(FCmatrix &A, Vec &v, int flag) 
{

    int m = A.GetRowN(); //linhas
    int n = A.GetColN(); //colunas
    int l = v.size();
    //cout << "m " << m << " n " << n << " l " << l << endl;
    if (l != m)
    {
        cout << "erro na dimensão m do sistema - GaussElimination" << endl;
        exit(1);
    }
    double *s;
    if (flag == 1) //no caso de pivotagem
    {
        s = new double[m];

        for (int i = 0; i < n; i++)
        {
            s[i] = A[i][A.GetRowMax(i)];
        }
    }

    int hR;
    int iR;

    for (int i = 0; i < m; i++)
    {
        if (flag == 1)
        {
            vector<double> rscale(n); //vetor scaling
            vector<double>::iterator maxpivot_;
            int maxpivot;

            for (int p = 0; p < m; p++)
            {
                int ix = A.GetRowIdx(p);
                rscale[ix] = fabs(A[ix][i]) / s[ix];
            }

            maxpivot_ = max_element(rscale.begin(), rscale.end());

            if (maxpivot_ != rscale.end())
            {
                maxpivot = distance(rscale.begin(), maxpivot_); //posição do pivot maior
                double C;
                int Ic = A.GetRowIdx(i);
                int maxpivotC = A.GetRowIdx(maxpivot);
                A.SetRowIdx(i, maxpivotC);
                A.SetRowIdx(maxpivot, Ic);
                C = v[i];
                v[i] = v[maxpivot];
                v[maxpivot] = C;
            }
        }

        if (flag == 0 && A[i][i] == 0.)
        {
            int p;
            for (p = i; A[p][i] == 0.; ++p)
            {
                ;
            }
            Swap(A, p, i);
        }

        for (int h = i + 1; h < m; h++) //linha pós pivot
        {
            hR = A.GetRowIdx(h);
            iR = A.GetRowIdx(i);

            if (A[hR][i] == 0.)
                continue;

            double lam = A[hR][i] / A[iR][i];

            for (int j = i; j < n; j++) //operação na linha
            {
                A[hR][j] = A[hR][j] - lam * A[iR][j];
            }
            v[hR] = v[hR] - lam * v[iR];
        }
    }
}

void FCmatrixAlgorithms::Swap(FCmatrix &mat, int a, int b)
{ //troca o a com o b
    Vec C;
    C = mat[b];
    //cout << C << endl;
    mat[b] = mat[a];
    mat[a] = C;

    //mat.SetRowIdx(a, b);
}

void FCmatrixAlgorithms::LUDecomposition(FCmatrix &A, int flag)
{

    int m = A.GetRowN(); //linhas
    int n = A.GetColN(); //colunas
    //cout << "mmin: " << mmin << endl;
    double *s;
    if (flag == 1)
    {
        s = new double[m];
        for (int i = 0; i < n; ++i)
        {
            s[i] = A[i][A.GetRowMax(i)];
            int a = A.GetRowMax(i);
            cout << "col max " << a << " ";
            cout << "valor si: " << s[i] << " ";
        }
    }

    int hR;
    int iR;

    for (int i = 0; i < m; ++i)
    {
        if (flag == 1)
        {
            vector<double> rscale(n); //vetor scaling
            vector<double>::iterator maxpivot_;
            int maxpivot;

            for (int p = 0; p < i; ++p)
                rscale[p] = 0.;
            for (int p = i; p < m; ++p)
            {
                int ix = A.GetRowIdx(p);
                //cout << " pivot: " << fabs(A[ix][i]) << "valor s[p]" << s[ix] << endl;
                rscale[p] = fabs(A[ix][i]) / s[ix];
                //cout << "___" << rscale[p] << "___________ : ";
            }

            maxpivot_ = max_element(rscale.begin(), rscale.end());

            if (maxpivot_ != rscale.end())
            {
                maxpivot = distance(rscale.begin(), maxpivot_); //posição do pivot maior
                //A.IdxPrint();
                int Ic = A.GetRowIdx(i);
                A.SetRowIdx(i, maxpivot);
                A.SetRowIdx(maxpivot, Ic);
                //A.IdxPrint();
                //A.Print();
            }
        }

        if (flag == 0 && A[i][i] == 0.)
        {
            int p;
            for (p = i; A[p][i] == 0; ++p)
            {
                ;
            }
            Swap(A, p, i);
            //A.Print();
        }

        for (int h = i + 1; h < m; ++h) //linha pós pivot
        {
            hR = A.GetRowIdx(h);
            iR = A.GetRowIdx(i);
            A.IdxPrint();

            if (A[hR][i] == 0.)
                continue;
            //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir "<< A[iR][i] << endl;
            double lam = A[hR][i] / A[iR][i];
            //cout << "lam: " << lam << endl;

            for (int j = i; j < n; ++j) //operação na linha
            {
                //cout << "avlor hr " << hR << " valor iR " << iR << endl;
                A[hR][j] = A[hR][j] - lam * A[iR][j];
                //A.Print();
            }
            A[hR][i] = lam;
            cout << endl;
        }
    }
}

Vec FCmatrixAlgorithms::GaussSolverBanded(FCmatrix &A, Vec &v, int flag) //para matriz das bandas
{

    int d = A.GetRowN(); //linhas
    cout << "avlor ded d linhas : " << d << endl;
    int l = v.size();
    //cout << "m " << m << " n " << n << " l " << l << endl;
    if (l != d)
    {
        cout << "erro na dimensão m do sistema - GaussElimination" << endl;
        exit(1);
    }

    for (int i = 1; i < d; ++i) //linha pivot 1
    {

        /*  if (A[i][i] == 0.)
        {
            int p;
            for (p = i; A[p][i] == 0; ++p)
            {
                ;
            }
            Swap(A, p, i);
            A.Print();
        }*/
        //cout << "valor h: " << h << "valor hr: " << hR<< endl;
        //cout << "Ahr" << A[hR][i] << "air" << A[iR][i] << endl;

        if (A[0][i] == 0.)
            continue;

        //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir " << A[iR][i] << endl;
        double lam = A[0][i - 1] / A[1][i - 1];

        //cout << "lam: " << lam << endl;
        A[1][i] = A[1][i] - lam * A[2][i - 1];
        A[0][i - 1] = 0.;
        if (i > 0)
        {
            v[i] = v[i] - lam * v[i - 1];
        }
    }

    //FCmatrixAlgorithms::GaussEliminationBanded(M[0], b);
    if (flag == 1)
    {
        double *x = new double[d + 1];

        x[d - 1] = v[d - 1] / A[1][d - 1];

        for (int k = d - 2; k >= 0; k--)
        {
            x[k] = (v[k] - A[2][k] * x[k + 1]) / A[1][k];
            //cout << "valor A1k : " << A[1][k] << "valor A2k : " << A[2][k] << endl;
            //cout << "k: " << k << "x[k]" << x[k] << endl;
        }

        Vec res(d, x);

        delete[] x;
        return res;
    }

    Vec D(d);
    return D;
}

void FCmatrixAlgorithms::LuDecompositionBanded(FCmatrix &A) //para matriz de bandas
{

    int d = A.GetRowN(); //linhas

    for (int i = 0; i < d; ++i) //linha pivot 1
    {

        /*  if (A[i][i] == 0.)
        {
            int p;
            for (p = i; A[p][i] == 0; ++p)
            {
                ;
            }
            Swap(A, p, i);
            A.Print();
            }
        }*/
        //cout << "valor h: " << h << "valor hr: " << hR<< endl;
        //cout << "Ahr" << A[hR][i] << "air" << A[iR][i] << endl;

        if (A[0][i] == 0.)
            continue;

        //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir " << A[iR][i] << endl;
        double lam = A[0][i] / A[1][i];
        //cout << "lam: " << lam << endl;
        A[1][i] = A[1][i] - lam * A[2][i];
        A[0][i] = lam;
    }
}