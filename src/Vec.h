#ifndef __Vec__
#define __Vec__

#include <iostream>

#include <vector>
#include "string.h"

using namespace std;

class Vec
{

public:
    //construtores
    Vec(int i = 0, double x = 0);
    Vec(int, const double *);
    Vec(const Vec &);

    //destrutor
    ~Vec();

    //operadores que manipulam o vetor
    double &operator[](int i);
    double operator[](int i) const;
    void operator=(const Vec &);
    Vec &operator+=(Vec &);
    Vec operator*(double) const;

    double dot(Vec &);
    void swap(int, int);
    double sumAbs();

    //definir um novo vetor
    void SetEntries(int, double *);

    //tamanho do vetor
    int size() const;

    //friend method
    friend ostream &operator<<(ostream &, const Vec &);

private:
    int N;
    double *entries;
};

#endif
