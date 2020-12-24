#include "FCmatrixAlgorithms.h"
#include <algorithm>
#include <cmath>

using namespace std;

void FCmatrixAlgorithms::GaussElimination(FCmatrixFull &A, Vec &v, int flag) //hipotese coluna de zeros não incluida
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
    if (flag == 1)
    {
        s = new double[m];
        for (int i = 0; i < n; ++i)
        {
            s[i] = A[i][A.GetRowMax(i)];
            //int a = A.GetRowMax(i);
            //cout << "col max " << a << " ";
            //cout << "valor si: " << s[i] << " ";
        }
    }

    int hR;
    int iR;

    for (int i = 0; i < m - 1; ++i)
    {
        if (flag == 1)
        {
            vector<double> rscale(n); //vetor scaling
            vector<double>::iterator maxpivot_;
            int maxpivot;

            for (int p = 0; p < i; ++p)
            {
                int ix = A.GetRowIdx(p);
                rscale[ix] = 0.;
            }
            for (int p = i; p < m; ++p)
            {
                int ix = A.GetRowIdx(p);
                //cout << " pivot: " << fabs(A[ix][i]) << "valor s[p]" << s[ix] << endl;
                rscale[ix] = fabs(A[ix][i]) / s[ix];
                cout << "___" << rscale[ix] << "___________ : ";
            }

            maxpivot_ = max_element(rscale.begin(), rscale.end());

            if (maxpivot_ != rscale.end())
            {
                maxpivot = distance(rscale.begin(), maxpivot_); //posição do pivot maior
                //A.IdxPrint();
                //cout << "maxpivot: " << maxpivot << endl;
                double C;
                int Ic = A.GetRowIdx(i);
                //cout << "IC: " << Ic << "i : " << i << endl;
                A.SetRowIdx(i, maxpivot);
                int mi;
                for (mi = 0; mi < m; mi++)
                {
                    if (A.GetRowIdx(maxpivot) == mi)
                        break;
                }
                //cout << "mI: " << mi << endl;
                A.SetRowIdx(mi, Ic);
                C = v[i];
                v[i] = v[maxpivot];
                v[mi] = C;
                cout << "rwo: "
                     << endl;
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
            //cout << "valor h: " << h << "valor hr: " << hR<< endl;
            //cout << "Ahr" << A[hR][i] << "air" << A[iR][i] << endl;

            if (A[hR][i] == 0.)
                continue;

            //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir " << A[iR][i] << endl;
            double lam = A[hR][i] / A[iR][i];
            //cout << "lam: " << lam << endl;

            for (int j = i; j < n; ++j) //operação na linha
            {
                //cout << "avlor hr " << hR << " valor iR " << iR << endl;
                A[hR][j] = A[hR][j] - lam * A[iR][j];
                v[hR] = v[hR] - lam * v[iR];
                //cout << "jhti" << endl;
            }
        }
    }
}

void FCmatrixAlgorithms::Swap(FCmatrixFull &mat, int a, int b)
{ //troca o a com o b
    Vec C;
    C = mat[b];
    cout << C << endl;
    mat[b] = mat[a];
    mat[a] = C;
    //mat.SetRowIdx(a, b);
}

void FCmatrixAlgorithms::LUDecomposition(FCmatrixFull &A, int flag)
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
            //int a = A.GetRowMax(i);
            //cout << "col max " << a << " ";
            //cout << "valor si: " << s[i] << " ";
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
            {
                int ix = A.GetRowIdx(p);
                rscale[ix] = 0.;
            }
            for (int p = i; p < m; ++p)
            {
                int ix = A.GetRowIdx(p);
                //cout << " pivot: " << fabs(A[ix][i]) << "valor s[p]" << s[ix] << endl;
                rscale[ix] = fabs(A[ix][i]) / s[ix];
                //cout << "___" << rscale[p] << "___________ : ";
            }

            maxpivot_ = max_element(rscale.begin(), rscale.end());

            if (maxpivot_ != rscale.end())
            {
                maxpivot = distance(rscale.begin(), maxpivot_); //posição do pivot maior
                //A.IdxPrint();
                int Ic = A.GetRowIdx(i);
                int mi;
                for (mi = 0; mi < m; mi++)
                {
                    if (A.GetRowIdx(maxpivot) == mi)
                        break;
                }
                A.SetRowIdx(i, maxpivot);
                A.SetRowIdx(mi, Ic);
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
            //cout << endl;
        }
    }
}

Vec FCmatrixAlgorithms::GaussSolverBanded(FCmatrixBanded &A, Vec &v, int flag) //flag faz logo fase de substituição do sistema Ax = b
{

    int d = A.GetRowN(); //linhas
    int l = v.size();
    //cout << "m " << m << " n " << n << " l " << l << endl;
    if (l != d)
    {
        cout << "erro na dimensão m do sistema - GaussElimination" << endl;
        exit(1);
    }

    for (int i = 1; i < d; ++i) //linha pivot 1
    {
        if (A[0][i] == 0.)
            continue;

        //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir " << A[iR][i] << endl;
        double lam = A[0][i - 1] / A[1][i - 1];

        //cout << "lam: " << lam << endl;
        A[1][i] = A[1][i] - lam * A[2][i - 1];
        A[0][i - 1] = 0.;
        if (i > 0)
            v[i] = v[i] - lam * v[i - 1];
    }

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

void FCmatrixAlgorithms::LuDecompositionBanded(FCmatrixBanded &A)
{

    int d = A.GetRowN(); //linhas

    for (int i = 0; i < d; ++i) //linha pivot 1
    {
        if (A[0][i] == 0.)
            continue;

        //cout << "valor A[hR][iR]" << A[hR][i] << "  valot A[ir<]ir " << A[iR][i] << endl;
        double lam = A[0][i] / A[1][i];
        //cout << "lam: " << lam << endl;
        A[1][i] = A[1][i] - lam * A[2][i];
        A[0][i] = lam;
    }
}