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
  FCmatrix(const vector<Vec>&, string s = "matrix"); 
  FCmatrix(const FCmatrix&, string s = "matrix");

  virtual ~FCmatrix();

  // methods
  virtual int GetRowN() const; // number of rows
  virtual int GetColN() const; // number of columns  
 

  //metodos puramente virtuais
  virtual Vec& operator[](int) = 0;
  virtual double Determinant()  = 0;
  
  // friend methods
  friend ostream& operator<< (ostream&, const FCmatrix& );
  
  
 protected:
  // nb of rows = vector.size()
  // nb of columns = Vec.size() 
  vector<Vec> M;
  string classname;
  
};

#endif