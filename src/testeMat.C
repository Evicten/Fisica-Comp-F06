#include <algorithm>
#include <iostream>
#include "FCmatrixAlgorithms.h"
#include "Vec.h"
#include "EqSolver.h"
#include "FCmatrixBanded.h"

int main()
{

    double **mat = new double *[3];
    for (int i = 0; i < 3; ++i)
        mat[i] = new double[3];

    mat[0][0] = 1.;
    mat[0][1] = 0.;
    mat[0][2] = 0.;
    mat[1][0] = 1.;
    mat[1][1] = 0;
    mat[1][2] = 0;
    mat[2][0] = 1.;
    mat[2][1] = 0.;
    mat[2][2] = 0.;

    Vec B(3);

    /* FCmatrixFull FCmat(mat, 3, 3);
    FCmatrixFull FCmatR(mat, 3, 3);
    FCmatrixFull FCmatI = FCmat.operator+(FCmat);
    FCmatI.Print();
*/
    /*

    FCmatrixAlgorithms::LUDecomposition(FCmat, 0);

    FCmatrixAlgorithms::GaussElimination(FCmat,B, 0);
    FCmat.Print();*/

    /* double **mat2 = new double *[3]; //5x5
    for (int i = 0; i < 3; ++i)
        mat2[i] = new double[5];

    int p = 0;
    for (int i = 0; i < 3; ++i){
        for(int k = 0; k < 5; ++k){
        mat2[i][k] = p;
        }
        p = p+1;
    }
    
    cout << "aqui " << endl;
    
    Vec C(5, 1.);

    FCmatrixBanded mat5(mat2, 5);
    mat5.Print();
    cout << mat5.Determinant() << endl;
    cout << "Gauss elimination" << endl;
    //FCmatrixAlgorithms::LuDecompositionBanded(mat5);
    mat5.Print();

    cout << "Hi" << endl;

    //Hello.Print();
    cout << "Gauss" << endl;
    cout << FCmatrixAlgorithms::GaussSolverBanded(mat5, C, 1) << endl;

    double lam = 3.;*/

    // cout << C << endl;

    //FCmatrixBanded FCmatRes;
    //C = mat5.operator*(C);
    //cout << "ola" << endl;
    //FCmatRes.Print();

    cout << "resultado" << endl;

    //cout << C << endl;

    int n = 3;

    double **matRes = new double *[n];
    for (int i = 0; i < n; i++)
    {
        matRes[i] = new double[n];
    }
    vector<Vec> I;

    Vec nul(n);
    for (int i = 0; i < n; i++)
    { //matrix identidade suponho xD
        I.push_back(nul);
        I[i][i] = 1.;
    }

    FCmatrixFull identi(I);
    FCmatrixFull Mat(mat, n, n);

    EqSolver Res_aux(Mat, I[0]);

    for (int i = 0; i < n; i++)
    {
        if (i != 0)
        {
            Res_aux.SetConstants(I[i]);
        }
        cout << "-------------------vetor---------------" << endl;
        cout << I[i] << endl;
        cout << " -----------eliminacão gauss ----" << endl;
        Vec d = Res_aux.GaussEliminationSolver(0);
        Res_aux.Print();
        cout << "resulatdo-------------d---------" << endl;
        cout << d << endl;

        for (int j = 0; j < n; j++)
        {
            matRes[j][i] = d[j];
        }
    }

    cout << "passou" << endl;

    FCmatrixFull A(matRes, n, n);
    cout << "152 pass" << endl;

    return 1;
}