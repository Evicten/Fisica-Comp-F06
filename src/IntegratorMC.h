#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "Func1D.h"
#include "TF2.h"
#include <iostream>

using namespace std;

class IntegratorMC : public Func1D{

    public:

    IntegratorMC(TF1 *fp = nullptr) :Func1D(fp), f2D(nullptr) {;}
    IntegratorMC(TF2* fp = nullptr) : Func1D(nullptr){
        f2D = new TF2(*fp);
        cout << __PRETTY_FUNCTION__ << endl;
    }
    ~IntegratorMC();

    //set function
    void SetIntegrandFunction(TF1*);
    void GetRange2D(double&, double&, double&, double&);

    //void GetRange2D();

    //simple integration
    void IntegralMC(int, double&, double&); //xmin, xmax, N, result, error, pdf

    //importance sampling
    void IntegralMCIS(int&, double&, double&, TF1*, TF1*);//xmin, xmax, N, result, erro, pdf, x(y)

    //acceptance rejection
    //funciona somente para funcoes positivas pelo que vi
    void IntegralMCAR(int, double&, double&); //without a given pdf, uses uniform
    void IntegralMCAR(int, double&, double&, TF1*, TF1*, TF1*); //given a pdf by the user


    //multi-dimension integral
    //brute-force
    void IntegralMCBF(int, double&);


    //limits goes inside TF
    protected:
    TF2* f2D;


};

#endif