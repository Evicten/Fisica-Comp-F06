#ifndef __DataReader__
#define __DataReader__

#include <vector>
#include <utility>
#include <string>
#include "TGraph.h"

using namespace std;

class DataReader
{

    //atributo
private:
    vector<pair<double, double>> sunSpotsT;

    //construtores
public:
    DataReader(string file = " ");
    ~DataReader();

    //métodos para aceder ao atributo
public:
    vector<pair<double, double>> GetDataVector(); //(time, value)
    TGraph *GetDataGraph();

public:
    //métodos de leitura de dados
    vector<string> split(string, string);
    static bool FileExists(string);
};

#endif