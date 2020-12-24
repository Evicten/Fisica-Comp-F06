#include "Motion.h"
#include "Uniform1D.h"
#include <iostream>

using namespace std;

Uniform1D::Uniform1D(int fN, float Ti, float Xi, float Dt, float Vel) : Motion(fN){
    t[0] = Ti;
    x[0] = Xi;
    for(int i = 1; i < fN; ++i)
    {
        x[i] = x[i-1] + Vel*Dt;
        t[i] = t[i] + Dt;
    }
}

void Uniform1D::Print(){
    Motion::Print();
    cout << "vel" << " = " << vel << " : " << "xi" << " : " << xi << endl; 
}