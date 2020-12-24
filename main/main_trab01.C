#include <algorithm>
#include <iostream>
#include "FCmatrixAlgorithms.h"
#include "Vec.h"
#include "EqSolver.h"

int main()
{

  /*
  double a[]{1., 3., 59., 7., 800., 5000., 0., 3., 5., 59., 6., 1., 68888888888., 7777777777777777777778., 9., 170770919.};
  double vj = 2.;
  double vk = 1.;
  double vv[3][3]{{2., -2., -1.}, {-2., 4., 8.}, {-6., 3., 2.}};
  double vb[]{16, 0, 1};
  double *v = new double[10];
  for (int i = 0; i < 10; ++i)
  {
    v[i] = vj;
    vj = vj + vk;
  }

  double **mat = new double *[3];
  for (int i = 0; i < 3; ++i)
    mat[i] = new double[3];

  mat[0][0] = 7.;
  mat[0][1] = 2.;
  mat[0][2] = 0.;
  mat[1][0] = 3.;
  mat[1][1] = 4;
  mat[1][2] = -2;
  mat[2][0] = 9;
  mat[2][1] = -2;
  mat[2][2] = 4;
  Vec A(10, v);
  Vec B(3, vb);

  double **mat2 = new double *[3];
  for (int i = 0; i < 3; ++i)
    mat2[i] = new double[3];

  mat2[0][0] = 1.;
  mat2[0][1] = 0.;
  mat[0][2] = 0.;
  mat2[1][0] = 0.;
  mat2[1][1] = 1.;
  mat2[1][2] = 0.;
  mat2[2][0] = 0.;
  mat2[2][1] = 0.;
  mat2[2][2] = 1.;

  FCmatrixFull FCmat(mat, 3, 3);
  FCmatrixFull FCmat1(mat, 3, 3);
  FCmatrixFull FCmat2(mat2, 3, 3);

  FCmat1.Print();
  cout << " ---------------" << endl;

  FCmatrixAlgorithms::GaussElimination(FCmat1, B, 1);

  FCmat1.Print();
  double ttt = FCmat1.Determinant();
  cout << ":: :" << ttt << endl;

*/
  //Vec teste = FCmat.GetRow(0);
  //cout << teste << endl;
  //int h = FCmat1.GetColMax(1);
  //cout << "valor11: " <<  h << endl;

  //cout << "valor máximo coluna 1" << FCmat.GetRowMax(0) <<endl;
  /* cout << "gauss " << endl;
     FCmat2.Print();
    FCmatrixAlgorithms::GaussElimination(FCmat1, B, 1);
     FCmat1.Print();*/
  //Vec v_ = EqSolver::GaussEliminationSolver(FCmat1, B);
  //cout << v_ << endl;

  //FCmat.Print();

  // cout << "valor: " << FCmat[1][2] << endl;

  /*cout << "Lu" << endl;
    cout << "gauss " << endl;
    FCmat2.Print();
    FCmatrixAlgorithms::GaussElimination(FCmat1,B, 0);
    FCmat1.Print();
    FCmatrixAlgorithms::GaussElimination(FCmat1,B, 1);
    FCmat1.Print();*/
  /*Vec vlu = EqSolver::LUDecompositionSolver(FCmat1, B);
    cout << vlu << endl;*/

  /*FCmatrixAlgorithms::LUDecomposition(FCmat1, B, 1);
    FCmat1.Print();*/

  //FCmatrix

  /*FCmatrix* matF1;

  matF1 = new FCmatrixFull();
  matF1->Print();

  FCmatrixFull matCpy(FCmat1);
  matCpy.Print();

  cout << "aqiu" << endl;

  
  EqSolver FG1(FCmat2, B);
  EqSolver FG2(FCmat2, B);
  EqSolver FG3(FCmat2, B);
  //FG.SetMatrix(FCmat2);

  //FG.Print();

  cout << "jnjnbj" << endl;
  Vec reseq1 = FG2.JacobiIter();
  cout << reseq1 << endl;
  cout << "LU" << endl;
  Vec reseq0 = FG3.LUDecompositionSolver(1);
  cout << reseq0 << endl; 
  Vec reseq2 = FG1.GaussEliminationSolver(1);
  cout << reseq2 << endl;*/

  /*
  double *M = new double[4];
  M[0] = 2.;
  M[1] = 3.;
  M[2] = 10.;
  M[3] = 6.;

  // condição j maior ou igual a 1
  vector<double> line(4);
  vector<double>::iterator maxi;
  for (int i = 0; i < 4; ++i)
  {
    line[i] = M[i];
    cout << "valor. " << line[i] << "  " << endl;
  }

  maxi = max_element(line.begin(), line.end());
  cout << "valor mamnmn" << distance(line.begin(), maxi) << endl;

  */

  cout << "------------testes vi--------------" << endl;

  double **matVi = new double *[3];
  for (int i = 0; i < 3; ++i)
    matVi[i] = new double[3];

  matVi[0][0] = 4.;
  matVi[0][1] = -2.;
  matVi[0][2] = 1.;
  matVi[1][0] = -2.;
  matVi[1][1] = 4;
  matVi[1][2] = -2;
  matVi[2][0] = 1;
  matVi[2][1] = -2;
  matVi[2][2] = 4;

  FCmatrixFull FCmatVi(matVi, 3, 3);

  double bVi[]{11, -16, 17};

  Vec B(3, bVi);

  FCmatVi.Print();

  FCmatrixAlgorithms::GaussElimination(FCmatVi, B, 1);

  FCmatVi.Print();

  return 1;
}