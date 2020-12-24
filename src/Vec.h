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

    void SetEntries(int, double*);
    
    int size();
    double dot(Vec&);
    void swap(int, int);
    double sumAbs();


    void operator=(const Vec&);
    Vec& operator+=( Vec&);

    Vec operator*(double) const;

    friend ostream& operator<<(ostream&, const Vec&);

    private:
    int N;
    double *entries;
    
};


#endif
