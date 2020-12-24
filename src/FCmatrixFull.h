#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"


class FCmatrixFull : public FCmatrix{

    public:
    FCmatrixFull();
    FCmatrixFull(double**, int, int);
    FCmatrixFull(double*, int, int);
    FCmatrixFull(const vector<Vec>&);

    FCmatrixFull(const FCmatrix&);// constructor
    ~FCmatrixFull(); 

    //operators
    const FCmatrixFull& operator=(const FCmatrixFull&);
    FCmatrixFull operator+(const FCmatrixFull&);
    Vec& operator[](int);
    Vec operator[](int) const;
    FCmatrixFull operator-(const FCmatrixFull&);
    FCmatrixFull operator*(double lambda);
    FCmatrixFull operator*(const FCmatrixFull&); //M*mat&
    Vec operator*(const Vec&);
    
    //operadores que manipulam a matriz
    Vec GetRow(int);
    int GetRowMax(int i = 0) const;
    int GetColMax(int j = 0) const;
    void Setvector(const vector<Vec>&);

    double Determinant();

    //metodos para uteis em troca de linhas
    void SetRowIdx(int, int);
    void IdxPrint() const;
    int GetRowIdx(int) const;

    //friend method
    friend ostream& operator<<(ostream&, const FCmatrixFull&);
    

    private:
    int *rowindices;

};

#endif