#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"


class FCmatrixFull : public FCmatrix{

    public:
    FCmatrixFull();
    FCmatrixFull(double**, int, int);
    FCmatrixFull(double*, int, int);
    FCmatrixFull(vector<Vec>&);

    
    FCmatrixFull(FCmatrix&);// constructor
    FCmatrixFull(FCmatrixFull&);

    //operators
    FCmatrixFull operator+(FCmatrix&);
    Vec& operator[](int);
    FCmatrixFull operator-(FCmatrix&);
    FCmatrixFull operator*(double lambda);
    FCmatrixFull operator*(FCmatrix&); //M*mat&
    Vec operator*(Vec&);

    double Determinant();
    
    Vec GetRow(int);
    void Print();
    int GetRowMax(int i = 0);
    int GetColMax(int j = 0);


    void SetRowIdx(int, int);
    void IdxPrint();
    int GetRowIdx(int);

    void Setvector(vector<Vec>&);
    

    private:
    int *rowindices;

};

#endif