#ifndef __DataPoints__
#define __DataPoints__

#include <string>
#include "TGraph.h"

using namespace std;

class DataPoints{
    public:
    DataPoints();
    DataPoints(int, double*, double*);
    virtual ~DataPoints();

    virtual TGraph* GetGraph();
    virtual void Print(string FILE = " ");


    protected:
    int N; //number of data points jk
    double *x, *y; //arrays
};

#endif