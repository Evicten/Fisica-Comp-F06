#include "DataPoints.h"
#include <iostream>
#include <algorithm>

using namespace std;

DataPoints::DataPoints() : N(0), x(nullptr), y(nullptr) {;}

DataPoints::DataPoints(int n, double *xData, double *yData) : N(n), x(new double[N]), y(new double[N]){
    copy(xData, xData + N, x);
    copy(yData, yData + N, y);
}

DataPoints::~DataPoints()
{
    delete[] x;
    delete[] y;
}

TGraph* DataPoints::GetGraph(){
    TGraph *g = new TGraph(N, x, y);
    g->SetMarkerStyle(20);
    g->SetMarkerColor(kRed);
    g->SetMarkerSize(2.5);
    return g;
}

void DataPoints::Print(string FILE)
{

    cout << FILE << endl;
    for (int i = 0; i < N; ++i)
        cout << " x[" << i << "]= " << x[i];
    for (int i = 0; i < N; ++i)
        cout << " y[" << i << "]= " << y[i];

    cout << endl;
}