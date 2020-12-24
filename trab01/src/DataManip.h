#ifndef __DataManip__
#define __DataManip__

#include <vector>
#include <utility>
#include "DataReader.h"
#include "TH2D.h"

using namespace std;

class DataManip : public DataReader
{
    //construtores
public:
    DataManip(string);
    // ~DataManip();

    //métodos de manipulação de dados
public:
    vector<pair<double, double>> GetDataVectorSorted(int);
    vector<pair<double, double>> GetDataDerivativeVector();
    vector<pair<double, double>> GetMovingAverage(int);
    TGraph *GetDataDerivativeGraph();
    TH1D *GetDataDerivativeHisto();
    TGraph *GetMovingAverageGraph(int, string);
    double meanX(double, vector<pair<double, double>>);
    double meanX2(double, vector<pair<double, double>>);
    vector<pair<double, double>> GetRoverK(double, double, double);
    TGraph *GetAutocorrelationGraph(double, double, double, string);
};

#endif