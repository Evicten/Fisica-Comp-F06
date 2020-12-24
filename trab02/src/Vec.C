#include "Vec.h"
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include "TROOT.h"
#include <vector>
#include <numeric>
#include <cmath>

//#define DEBUG

using namespace std;

// constructors

Vec::Vec(int i, double x) : N(i)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (N < 0)
  throw invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  entries = new double[N];
  fill_n(entries, N, x);
}

Vec::Vec(int i, const double *x) : Vec(i)
{ //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (x)
    copy(x, x + i, entries);
    else
    throw invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
}

Vec::Vec(const Vec &v) : Vec(v.N, v.entries)
{ //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}
//destructor
Vec::~Vec()
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  delete[] entries;
}

// operators
double &Vec::operator[](int i)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i >= N)
  throw invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));
  return entries[i];
}

double Vec::operator[](int i) const
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i >= N)
  throw invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));
  return entries[i];
}


void Vec::operator=(const Vec &v)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &v)
  {
    if (v.N != N)
    {
      N = v.N;
      delete[] entries;
      entries = new double[N];
    }
    copy(v.entries, v.entries + N, entries);
  }
}

Vec &Vec::operator+=(Vec &v)
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (v.N != N)
  {
   throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
  }
  for (int i = 0; i < N; ++i)
  {
    entries[i] += v[i];
  }
  return *this;
}

Vec Vec::operator-(Vec& v) const
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (v.N != N)
  {
   throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
  }
  for (int i = 0; i < N; ++i)
  {
    entries[i] = entries[i] - v[i];
  }
  return *this;
}

Vec Vec::operator*(double x) const
{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (abs(x - 1.) < 1E-9)
    return *this;
  double a[N];
  for (int i = 0; i < N; ++i)
  {
    a[i] = entries[i] * x;
  }
  return Vec(N, a);
}

///////////////////// friend methods

std::ostream &operator<<(std::ostream &s, const Vec &v)
{
  s << "[";
  for (int i = 0; i < v.N; ++i)
  {
    s << fixed << setprecision(3) << v.entries[i];
    if (i < v.N - 1)
      s << ", ";
  }
  s << "]";
  return s;
}

void Vec::SetEntries(int n, double *a)
{
  delete[] entries;
  N = n;
  cout << "valor de N: " << N << endl;
  entries = new double[N];
  entries = a;
}

int Vec::size() {
  return N;
}

int Vec::size() const {
  return N;
}

double Vec::dot(Vec& v){
  if(v.N != N)
  exit(1);

  return inner_product(entries, entries+N, v.entries, 0);
}

void Vec::swap(int i, int j){
  if(max(i, j) >= N)
  exit(1);

  if(i != j)
  swap(entries[i], entries[j]);
}

double Vec::sumAbs(){
  return accumulate(entries, entries+N, 0, [](double accum, double x){return accum+fabs(x);});
}

