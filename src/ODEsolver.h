#ifndef __ODEsolver__
#define __ODEsolver__

#include "ODEpoint.h"
#include "TF1.h"
#include <vector>
#include <ostream>

using namespace std;

class ODEsolver
{
public:
    ODEsolver(const vector<TF1> &);
    ~ODEsolver();

    void SetODEfunc(const vector<TF1> &);

    vector<ODEpoint> Euler(const ODEpoint &, double, double T);            //initial condition, step, tempo do fim da solucao
    vector<ODEpoint> PredictorCorrector(const ODEpoint &, double, double); //idem Euler
    vector<ODEpoint> RK2(const ODEpoint &, double, double);                //idem
    vector<ODEpoint> RK4(const ODEpoint &, double, double);                //idem
    //StormerV metodo de 2 ordem
    vector<ODEpoint> StormerV(const ODEpoint &, int, double, double); //intial condition, nb steps, instante do fim da solucao, dy/dt em t = t0

private:
    vector<TF1> F;
    //indices comecam em 0
};
#endif