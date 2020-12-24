#include <fstream>
#include <utility>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    fstream sunFile;
    string file = "SunspotNumberDATA2020.txt";
    sunFile.open(file, ios::in);

    // ver se foi aberto corretamento
    if (!sunFile)
    {
        cout << "Erro a abrir o ficheiro" << endl;
        exit(1);
    }

    cout << "file opened for reading...[" << file << "]" << endl;

    // read numbers to y array while file is readable
    double col[8];
    while (sunFile >> col[0] >> col[1] >> col[2] >> col[3] >> col[4] >> col[5] >> col[6] >> col[7])
    {
        if (col[0] < 1849 || col[0] > 2019)
            continue;

        cout << col[0] << " , " << col[1] << " , " << col[2] << endl;
    }
    sunFile.close();
}