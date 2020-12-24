#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"

class FCmatrixFull : public FCmatrix
{

public:
    FCmatrixFull();
    FCmatrixFull(double **, int, int);
    FCmatrixFull(double *, int, int);
    FCmatrixFull(vector<Vec> &);

    FCmatrixFull(FCmatrix &); // constructor
    FCmatrixFull(FCmatrixFull &);

    //operators
    FCmatrixFull operator+(FCmatrix &);
    Vec &operator[](int);
    Vec operator[](int) const;
    FCmatrixFull operator-(FCmatrix &);
    FCmatrixFull &operator=(FCmatrixFull &);
    FCmatrixFull operator*(double lambda);
    FCmatrixFull operator*(FCmatrix &); //M*mat&
    Vec operator*(Vec &);

    friend ostream &operator<<(ostream &, const FCmatrixFull &);

    double Determinant();

    Vec GetRow(int);
    void Print();
    int GetRowMax(int i = 0);
    int GetColMax(int j = 0);

    vector<Vec> GetMat();

    void SetRowIdx(int, int);
    void IdxPrint();
    int GetRowIdx(int) const;

    void Setvector(vector<Vec> &);

private:
    int *rowindices;
};

#endif