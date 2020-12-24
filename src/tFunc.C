#include "Func1D.h"
#include "Integrator.h"
#include "Derivator.h"
#include <iostream>

using namespace std;

int main()
{

    TF1 *func = new TF1("func", "x*sin(x)*sin(x)*sin(x)", -3, 4);

    Derivator B(1., 5., func);
    cout << "valor da derivada: " << B.Dx1(3.1415) << endl;
    cout << "---------------" << endl;

    Integrator C(1., 1.5, func);
    double Res = 0.;
    double erro = 0.0000001;

    cout << "-----------Adaptative-------" << endl;
    C.TrapezoidalAdaptative(Res, erro);
    cout << "valor integral trapez: " << Res << " erro: " << erro << endl;

    cout << "----------Trapez------" << endl;
    C.Trapezoidal(99, Res, erro);
    cout << "valor integral: " << Res << endl;
    cout << "erro: " << erro << endl;

    cout << "----------Romberg------" << endl;
    C.Romberg(99, Res, erro);
    cout << "valor integral: " << Res << endl;

    cout << "----------Simpson------" << endl;
    C.Simpson(99, Res, erro);
    cout << "valor integral: " << Res << endl;

    return 1;
}