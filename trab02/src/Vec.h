#ifndef __Vec__
#define __Vec__

#include <iostream>


#include <vector>
#include "string.h"

using namespace std;

class Vec{
    
    public:
    Vec(int i=0, double x=0);
    Vec(int, const double*);
    Vec(const Vec&);
    
    ~Vec();

   
    double& operator[](int i);
    double operator[](int i) const;

    void SetEntries(int, double*);
    
    int size();
    int size() const;
    double dot(Vec&);
    void swap(int, int);
    double sumAbs();


    void operator=(const Vec&);
    Vec& operator+=( Vec&);
    Vec operator*(double) const;
    Vec operator-(Vec&) const;

    friend ostream& operator<<(ostream&, const Vec&);

    private:
    int N;
    double *entries;
    
};


#endif
