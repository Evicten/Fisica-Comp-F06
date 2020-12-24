#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "Func1D.h"
#include "TF2.h"
#include <iostream>

using namespace std;

class IntegratorMC : public Func1D
{
public:
    IntegratorMC(const TF1 *fp = nullptr) : Func1D(fp), f2D(nullptr) { ; }
    IntegratorMC(const TF2 *fp = nullptr) : Func1D(nullptr)
    {
        f2D = new TF2(*fp);
        cout << __PRETTY_FUNCTION__ << endl;
    }
    ~IntegratorMC();

    //set function
    void SetIntegrandFunction(const TF1 *);
    void GetRange2D(double &, double &, double &, double &);

    //simple integration
    void IntegralMC(int, double &, double &); //N, result, error

    //importance sampling
    void IntegralMCIS(int &, double &, double &, const TF1 *, const TF1 *); //xmin, xmax, N, result, erro, pdf, x(y)

    //acceptance rejection
    //funciona somente para funcoes positivas pelo que vi
    void IntegralMCAR(int, double &, double &);                                        //without a given pdf, uses uniform
    void IntegralMCAR(int, double &, double &, const TF1 *, const TF1 *, const TF1 *); //given a pdf by the user

    //multi-dimension integral
    //brute-force
    void IntegralMCBF(int, double &);

private:
    TF2 *f2D;
    //limits goes inside TF
};

#endif