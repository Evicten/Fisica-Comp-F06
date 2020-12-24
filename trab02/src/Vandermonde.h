#ifndef __Vandermonde__
#define __Vandermonde__

#include "TF1.h"
#include "TGraph.h"
#include "FCmatrixFull.h"


class Vandermonde {

    public:

    //construtores e destrutor

    Vandermonde();
    Vandermonde(unsigned, double, double, const TF1&);
    ~Vandermonde();

    //Getters
    const Vec& GetCoefficients();
    const FCmatrixFull& GetMatrix();
    const double* GetX();
    const double* GetY();
    double GetCoefError();
    void GetInverseMatrix(FCmatrixFull&);

    //funcoes auxiliares p/ organizacao do codigo
    void calculateCoeffs();
    double Interpolate(double);

    //Graphics getters:
    TGraph& GetGraphPoints(); //return data points graph
    TF1& GetPolyFunc(); //return polynomial function

    private:

    //funcao auxiliar
    double fInterpolator(double *fx, double *par){
        return Interpolate(fx[0]);
    }

    //setters
    void SetGraphicsPoints(); //set graphics with data points
    void SetPolynomialFunction(); //set polynomial TF1 function

    //data members
    FCmatrixFull MatrixCoefs; //coeff matrix (C)
    Vec PolCoefs; //polynomial coeffs (a)

    TF1* fPoly; //polynomial function;
    TGraph gPoints; //point's graphics

    int n; // number points
    double* x;
    double* y;


};

#endif