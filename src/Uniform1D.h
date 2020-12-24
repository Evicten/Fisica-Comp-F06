#ifndef __Uniform1D__
#define __Uniform1D__

#include "Motion.h"

class Uniform1D : public Motion{
    public:
    Uniform1D(int fN = 0, float ti = 0., float xi = 0., float dt = 0., float vel = 0.);
    ~Uniform1D() = default;

    void Print();
    private:
    float ti;
    float dt;
    float xi;
    float vel;

};
#endif