#include "FCtools.h"
#include <fstream>

using namespace std;

vector<string> FCtools::split(string line, string delimiter)
{

  vector<string> final;
  string delimitir = " ";
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

vector<string> FCtools::ReadFile2String(string file)
{

  vector<string> Res;

  fstream mat;
  mat.open(file, ios::in);

  if (!mat)
  {
    cout << "Erro a abrir o ficheiro para ler a matriz" << endl;
    exit(1);
  }

  string line;
  while (getline(mat, line))
    Res.push_back(line);

  return Res;
}

vector<Vec> FCtools::ReadFile2Vec(string file)
{
  vector<Vec> Res;

  vector<string> Rs = FCtools::ReadFile2String(file);
  
  Vec A;
  string line;
  string delimiter = " ";
  for(int i = 0; i < Rs.size(); ++i)
  {
    vector<string> parsedLine = FCtools::split(Rs[i], delimiter);
    int n = parsedLine.size();
    double *a = new double[n];
    for (int i = 0; i < n; ++i)
    {
      double ele = stod(parsedLine[i]);
      a[i] = ele;
    }
    A.SetEntries(n, a);
    Res.push_back(A);
  }
  return Res;
}

Vec* ReadFile2Vecp(string file, int& rows){
    
    vector<Vec> A = FCtools::ReadFile2Vec(file);
  int l = A[0].size();
  double* v = new double[l];

  Vec *Res = new Vec[rows];
  for (int i = 0; i < rows; ++i)
  {
    for(int j = 0; j < l; ++j)
    v[i] = A[i][j];

    Res[i].SetEntries(l,v);
  }
    return Res;

}