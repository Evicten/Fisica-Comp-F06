#include "DataManip.h"
#include "DataReader.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include "math.h"

using namespace std;

#define LOG(x) std::cout << x << std::endl;

DataManip::DataManip(string file) : DataReader::DataReader(file)
{
    ;
}

vector<pair<double, double>> DataManip::GetDataVectorSorted(int option)
{

    vector<pair<double, double>> tvData = GetDataVector();

    /*for (int i = 0; i < tvData.size(); i++)
    {
        cout << tvData[i].first << ";" << tvData[i].second << endl;
    }*/
    /*vector<double> time, value;
    vector<pair<double, double>> vtData;

    for (pair<double, double>& v : tvData)
    {
        time.push_back(v->first);
        value.push_back(v->second);
    }

    for (int i = 0; i < tvData.size(); ++i)
        vtData.push_back(make_pair(value[i], time[i]));*/

    if (option == 0)
    {
        sort(tvData.begin(), tvData.end(), [](pair<double, double> &left, pair<double, double> &right) {
            return left.second > right.second;
        });
    }
    else if (option == 1)
    {
        sort(tvData.begin(), tvData.end(), [](pair<double, double> &left, pair<double, double> &right) {
            return left.second < right.second;
        });
    }
    else
    {
        cout << "Escreva como argumento desta função: 1 - ordem ascendente; 0 - ordem descendente" << endl;
    }
    return tvData;
}

vector<pair<double, double>> DataManip::GetDataDerivativeVector()
{
    vector<pair<double, double>> tvData = this->DataReader::GetDataVector();
    //vector<pair<double, double>> tvData = sunSpotsT;
    vector<double> value, time, derivative;
    double *dtime;
    double *dvalue;
    vector<pair<double, double>> Res;

    for (int i = 0; i < tvData.size(); ++i)
    {
        value.push_back(tvData[i].second);
        time.push_back(tvData[i].first);
    }

    dtime = new double[time.size()];
    dvalue = new double[value.size()];

    adjacent_difference(value.begin(), value.end(), dvalue);
    adjacent_difference(time.begin(), time.end(), dtime);

    for (int i = 1; i < time.size(); ++i)
    {
        double c = dvalue[i] / dtime[i];
        derivative.push_back(c);
    }

    for (int i = 1; i < time.size(); ++i)
    {
        pair<double, double> tderi;
        tderi = make_pair(time[i], derivative[i - 1]);
        Res.push_back(tderi);
    }

    return Res;
}

TGraph *DataManip::GetDataDerivativeGraph()
{

    vector<pair<double, double>> Data = this->DataManip::GetDataDerivativeVector();

    int size = Data.size();
    double *time = new double[size];
    double *value = new double[size];

    for (int i = 0; i < size; i++)
    {
        time[i] = Data[i].first;
        value[i] = Data[i].second;
    }

    TGraph *graph = new TGraph(size, time, value);
    graph->SetName("GdataDeriv");
    graph->SetTitle("GdataDeriv");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.4);
    graph->SetMarkerColor(kGreen + 2);

    return graph;
}

TH1D *DataManip::GetDataDerivativeHisto()
{

    vector<pair<double, double>> Data = this->DataManip::GetDataDerivativeVector();

    int size = Data.size();

    TH1D *hist = new TH1D("HdataDeriv", "HdataDeriv", size, 1849, 2020);

    for (pair<double, double> v : Data)
    {
        hist->Fill(v.first, v.second);
    }

    return hist;
}

vector<pair<double, double>> DataManip::GetMovingAverage(int N)
{
    vector<pair<double, double>> Res;
    vector<pair<double, double>> sData = GetDataVector();
    vector<double> s, s2, time;
    int size = sData.size();

    if (N % 2 == 0) //falta as outras restirçóes tbm
    {
        cout << "Escolher N impar" << endl;
        exit(1);
    }

    if (N > size / 2) //falta as outras restirçóes tbm
    {
        cout << "Escolher N menor que " << size / 2 << endl;
        exit(1);
    }

    for (int i = 0; i < size; i++)
        s.push_back(sData[i].second);

    for (int i = 0; i < size; i++)
        time.push_back(sData[i].first);

    int amp = (N - 1) / 2;

    for (int i = 0; i < amp; i++)
        s2.push_back(s[i]);

    for (int i = amp; i < (size - amp); i++)
    {
        double sum = 0.;
        for (int j = (i - amp); j <= (i + amp); j++)
            sum += s[j];

        sum = sum / (double)N;

        s2.push_back(sum);
    }

    for (int i = (size - amp); i < size; i++)
        s2.push_back(s[i]);

    for (int i = 0; i < size; i++)
        Res.push_back(make_pair(time[i], s2[i]));

    return Res;
}

TGraph *DataManip::GetMovingAverageGraph(int N, string name)
{
    vector<pair<double, double>> Data = GetMovingAverage(N);

    int size = Data.size();
    double *time = new double[size];
    double *value = new double[size];

    for (int i = 0; i < size; i++)
    {
        time[i] = Data[i].first;
        value[i] = Data[i].second;
    }

    TGraph *graph = new TGraph(size, time, value);
    graph->SetName(name.c_str());
    graph->SetTitle(name.c_str());
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.4);
    if (N < 100)
    {
        graph->SetMarkerColor(kYellow);
    }
    else
    {
        graph->SetMarkerColor(kMagenta);
    }

    return graph;
}

double DataManip::meanX(double k, vector<pair<double, double>> Data)
{
    int size = Data.size();
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (Data[i].first > 1849. + k)
        {
            break;
        }
        Data.erase(i + Data.begin());
    }

    double sum = 0;
    for (int j = 0; j < Data.size(); j++)
    {
        sum += Data[j].second;
    }
    return sum / Data.size();
}

double DataManip::meanX2(double k, vector<pair<double, double>> Data)
{
    int size = Data.size();
    int i = size - 1;
    for (i = size - 1; i > 0; i--)
    {
        if (Data[i].first < Data[size - 1].first - k)
        {
            break;
        }
        Data.erase(i + Data.begin());
    }

    double sum = 0;
    for (int j = 0; j < Data.size(); j++)
    {
        sum += Data[j].second;
    }
    return sum / Data.size();
}

vector<pair<double, double>> DataManip::GetRoverK(double kmin, double kmax, double timestep)
{
    vector<pair<double, double>> Data = GetDataVector();
    int size = Data.size();

    vector<pair<double, double>> Res;

    for (double k = kmin; k <= kmax; k += timestep)
    {
        double auxk = k * 365.;
        int daysk = (int)auxk;
        double numerador = 0;
        double denominador1 = 0;
        double denominador2 = 0;
        double mean_linha = meanX(k, Data);
        double mean_one = meanX2(k, Data);
        for (int i = 0; i + daysk <= size - 1; i++)
        {
            double xi = Data[i].second;
            double xik = Data[i + daysk].second;

            numerador += ((xi - mean_one) * (xik - mean_linha));
            denominador1 += (xi - mean_one) * (xi - mean_one);
            denominador2 += (xik - mean_linha) * (xik - mean_linha);
        }
        double R = numerador / (sqrt(denominador2 * denominador1));
        Res.push_back(make_pair(k, R));
    }
    return Res;
}

TGraph *DataManip::GetAutocorrelationGraph(double kmin, double kmax, double timestep, string name)
{
    vector<pair<double, double>> Data = GetRoverK(kmin, kmax, timestep);

    int size = Data.size();
    double *k = new double[size];
    double *R = new double[size];

    for (int i = 0; i < size; i++)
    {
        k[i] = Data[i].first;
        R[i] = Data[i].second;
    }

    TGraph *graph = new TGraph(size, k, R);
    graph->SetName(name.c_str());
    graph->SetTitle(name.c_str());
    graph->SetMarkerStyle(22);
    graph->SetMarkerSize(0.4);
    graph->SetMarkerColor(kGreen + 2);

    return graph;
}
