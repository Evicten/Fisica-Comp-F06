#ifndef __Func1D__
#define __Func1D__

#include "TF1.h"

class Func1D
{
public:
    Func1D(const TF1 *fp = nullptr);

    Func1D(const TF1 &);
    virtual ~Func1D();

    //drawing
    void Draw() const;

    //evaluate
    double Eval(double) const;

    //GetRange
    void GetRange(double &, double &);

protected:
    TF1 *f;
    void Settings();
};

#endif