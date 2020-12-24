#ifndef __FCmatrixBanded__
#define __FCmatrixBanded__

#include "FCmatrix.h"

class FCmatrixBanded : public FCmatrix
{

public: // a - linha 0 below diag | b - linha 1 diag | c - linha 2 up diag
    FCmatrixBanded();
    FCmatrixBanded(double **, int);
    FCmatrixBanded(vector<Vec> &);

    FCmatrixBanded(FCmatrix&);

    Vec GetRow(int i);
    void Print();

    //operators
    void operator=(FCmatrix &);
    FCmatrixBanded operator+(FCmatrix &);
    Vec &operator[](int);
    FCmatrixBanded operator-(FCmatrix &);
    FCmatrixBanded operator*(double lambda);
    FCmatrixBanded operator*(FCmatrix &); //M*mat& not defined
    Vec operator*(Vec &); //defined

    double Determinant();

    int GetRowMax(int i = 0);
    int GetColMax(int j = 0);

    //useless I think ----------------------
    void SetRowIdx(int, int);
    int GetRowIdx(int);
    void IdxPrint();
    void Setvector(vector<Vec> &);

    int GetRowN(); // number of rows
    int GetColN(); // number of columns redudndante mas prontos
    // -------------------------------------------
    //  private:
    // int *rowindices;
};

#endif