#include <fstream>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "DataReader.h"
#include "DataManip.h"

#define LOG(x) std::cout << x << std::endl;

using namespace std;

void printVector(vector<string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ";";
    }
    cout << endl;
}

int main()
{
    vector<pair<double, double>> vec = {{1903, 24}, {2005, 19}, {2010, 22}};
    string file = "SunspotNumberDATA2020.txt";
    DataManip D(file);
}
