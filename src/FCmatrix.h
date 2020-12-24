#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h"
#include <vector>
#include <iostream>
using namespace std;


class FCmatrix{

 public:

  // constructors
  FCmatrix(string s= "matrix");
  FCmatrix(double**, int, int, string s = "matrix"); // rows, columns
  FCmatrix(double*, int, int, string s = "matrix"); // rows, columns  
  FCmatrix( vector<Vec>&, string s = "matrix"); 
  FCmatrix(FCmatrix&, string s = "matrix");

  virtual ~FCmatrix();

  // methods
  virtual int GetRowN(); // number of rows
  virtual int GetColN(); // number of columns  
 

  //metodos puramente virtuais
  virtual Vec& operator[](int) = 0;
  virtual Vec GetRow(int i) = 0;
  virtual double Determinant() = 0;
  virtual void Print() = 0;

  virtual int GetRowMax(int i= 0) = 0;
  virtual int GetColMax(int j = 0) = 0;
  
  virtual void SetRowIdx(int, int) = 0;
  virtual int GetRowIdx(int) = 0;
  virtual void IdxPrint() = 0;
  virtual void Setvector(vector<Vec>&) = 0;
  // friend methods
  friend ostream& operator<< (ostream& ,FCmatrix& );
  
  
 protected:
  // nb of rows = vector.size()
  // nb of columns = Vec.size() 
  vector<Vec> M;
  string classname;
  
};

#endif