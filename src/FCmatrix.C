#include "FCmatrix.h"
#include <stdexcept>
#include <cstdio>
#include "TROOT.h"

using namespace std;

FCmatrix::FCmatrix(string s) : classname(s)
{
  Vec A;
  M.push_back(A);
}

FCmatrix::FCmatrix(double **a, int m, int n, string s) : classname(s)
{
  for (int i = 0; i < m; ++i)
  {
    M.emplace_back(n, a[i]);
    //Vec A(n, a[i]);
    //M.push_back(A);
  }
}

FCmatrix::~FCmatrix()
{
  M.clear();
}

FCmatrix::FCmatrix(double *a, int m, int n, string s) : classname(s)
{
  if (!a)
    // throw std::invalid_argument(Form("[%s] null pointer...!\n", __PRETTY_FUNCTION__));
    for (int i = 0; i < m; ++i)
    {
      M.emplace_back(n, &a[i * n]);
    }
}

FCmatrix::FCmatrix(vector<Vec> &v, string s) : classname(s)
{
  for (int i = 0; i < v.size(); ++i)
  {
    M.emplace_back(v[i]);
  }
}

FCmatrix::FCmatrix(FCmatrix &matrix, string s) : classname(s)
{
  for (int i = 0; i < matrix.GetRowN(); ++i)
  {
    M.emplace_back(matrix.M[i]);
  }
}

//methods

int FCmatrix::GetRowN()
{
  return M.size();
}

int FCmatrix::GetColN()
{
  return M[0].size();
}

// friend methods

ostream &operator<<(ostream &s, FCmatrix &matrix)
{
  s << "matrix: [\n";
  for (int i = 0; i < matrix.GetRowN(); ++i)
  {
    s << "           " << matrix.M[i] << "\n";
  }
  s << "        ]";
  return s;
}
