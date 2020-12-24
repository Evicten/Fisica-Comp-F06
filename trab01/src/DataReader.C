#include "DataReader.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

DataReader::DataReader(string file)
{
    //editar nome do ficheiro para reconhecê-lo no seu caminho
    file = "../" + file;
    cout << file << endl;

    //abrir o ficheiro
    fstream sunFile;
    sunFile.open(file, ios::in);

    cout << "file opened for reading...[" << file << "]" << endl;

    string line;                   //inicializar variáveis úteis
    string delimitir = " ";        //separador de informação
    while (getline(sunFile, line)) //por cada linha no ficheiro
    {
        vector<string> parsedLine = split(line, delimitir);
        double year = stod(parsedLine[3]);
        if (year >= 1849.)
            sunSpotsT.push_back(make_pair(year, stod(parsedLine[4])));
    }
    sunFile.close();
}

bool DataReader::FileExists(string file)
{
    fstream sunFile;

    file = "../" + file;
    cout << file << endl;
    sunFile.open(file, ios::in);

    // ver se foi aberto corretamento
    if (!sunFile)
    {
        cout << "Erro a abrir o ficheiro" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

DataReader::~DataReader()
{
    sunSpotsT.clear();
}

vector<string> DataReader::split(string line, string delimiter)
{
    {
        vector<string> final;
        size_t last = 0;
        size_t next = 0;
        while ((next = line.find(delimiter, last)) != string::npos)
        {
            string result = line.substr(last, next - last);
            if (result.compare("") != 0)
            {
                final.push_back(result);
            }
            last = next + 1;
        }
        return final;
    }
}

vector<pair<double, double>> DataReader::GetDataVector()
{
    return sunSpotsT;
}

TGraph *DataReader::GetDataGraph()
{
    int size = sunSpotsT.size();
    double *time = new double[size];
    double *value = new double[size];

    for (int i = 0; i < size; i++)
    {
        time[i] = sunSpotsT[i].first;
        value[i] = sunSpotsT[i].second;
    }

    TGraph *graph = new TGraph(size, time, value);
    graph->SetName("GData");
    graph->SetTitle("GData");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.4);
    graph->SetMarkerColor(kBlue + 1);

    return graph;
}
