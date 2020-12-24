#ifndef __FCmatrixBanded__
#define __FCmatrixBanded__

#include "FCmatrix.h"

class FCmatrixBanded : public FCmatrix
{
public: // a - linha 0 below diag | b - linha 1 diag | c - linha 2 up diag
    //construtores
    FCmatrixBanded();
    FCmatrixBanded(double **, int);
    FCmatrixBanded(const vector<Vec> &);
    FCmatrixBanded(const FCmatrix &);

    void Print();

    //operators
    void operator=(FCmatrixBanded &);
    FCmatrixBanded operator+(FCmatrixBanded &);
    Vec &operator[](int);
    FCmatrixBanded operator-(FCmatrixBanded &);
    FCmatrixBanded operator*(double lambda);
    FCmatrixBanded operator*(FCmatrixBanded &); //M*mat& not defined
    Vec operator*(const Vec &);                 //defined

    double Determinant();

    int GetRowN(); // number of rows
    int GetColN(); // number of columns redudndante mas prontos
};

#endif