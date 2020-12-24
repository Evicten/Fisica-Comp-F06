#include "ODEsolver.h"
#include <iostream>

using namespace std;

//construtor-------------
ODEsolver::ODEsolver(const vector<TF1> &A)
{
    for (int i = 0; i < A.size(); i++)
        F.push_back(A[i]);
}
//----------------------

//Destrutor-----------------
ODEsolver::~ODEsolver()
{
    F.clear();
}
//--------------------

void ODEsolver::SetODEfunc(const vector<TF1> &B)
{

    F.clear();
    for (int i = 0; i < B.size(); i++)
        F.push_back(B.at(i));
}

//Metodos para resolver um sistema de eqauações diferenciais
vector<ODEpoint> ODEsolver::Euler(const ODEpoint &y0, double h, double T)
{
    //cout << __PRETTY_FUNCTION__ << endl;
    vector<ODEpoint> aux;
    aux.push_back(y0);
    ODEpoint yaux(y0);

    double t = y0.T();
    double n = y0.Ndim() + 1;
    int Nh = 1 + int(T / h);

    cout << "valor n: " << n << endl;
    for (int i = 0; i < Nh; i++)
    {
        for (int i = 1; i < n; i++)
            yaux[i] += h * F[i - 1].Eval(t, yaux[i]);

        t += h;
        yaux[0] = t;
        aux.push_back(yaux);
    }
    return aux;
}

vector<ODEpoint> ODEsolver::PredictorCorrector(const ODEpoint &y0, double h, double T)
{
    vector<ODEpoint> aux;
    ODEpoint yaux(y0);
    ODEpoint K1(y0);
    double t = y0.T();
    double n = y0.Ndim() + 1;

    int Nh = 1 + int(T / h);
    for (int i = 0; i < Nh; i++)
    {
        K1[0] = t;
        for (int i = 1; i < n; i++)
            K1[i] += h * F[i - 1].Eval(t, K1[i]);

        yaux[0] = t;
        for (int i = 1; i < n; i++)
            yaux[i] += 0.5 * h * (K1[i] + yaux[i]);

        t += h;
        yaux[0] = t;
        aux.push_back(yaux);
    }
    return aux;
}

vector<ODEpoint> ODEsolver::RK2(const ODEpoint &y0, double h, double T)
{
    vector<ODEpoint> aux;
    ODEpoint K1(y0);
    ODEpoint K2(y0);
    ODEpoint yaux(y0);
    double t = y0.T();
    double n = y0.Ndim() + 1;

    int Nh = 1 + int(T / h);
    for (int i = 0; i < Nh; i++)
    {
        K1[0] = t;
        for (int i = 1; i < n; i++)
            K1[i] = h * F[i - 1].Eval(t, yaux[i]);

        K2[0] = t + 0.5 * h;
        for (int i = 0; i < n; i++)
            K2[i] = h * F[i - 1].Eval(t + 0.5 * h, yaux[i] + K1[i] * 0.5);

        yaux = (yaux + K2);
        t = t + h;

        yaux[0] = t;
        aux.push_back(yaux);
    }
    return aux;
}

vector<ODEpoint> ODEsolver::RK4(const ODEpoint &y0, double h, double T)
{
    vector<ODEpoint> aux;
    aux.push_back(y0);

    ODEpoint K1(y0);
    ODEpoint K2(y0);
    ODEpoint K3(y0);
    ODEpoint K4(y0);
    ODEpoint yaux(y0);
    double t = y0.T();
    double n = y0.Ndim() + 1;
    int Nh = 1 + int(T / h);

    for (int i = 1; i < Nh; i++)
    {
        K1[0] = t;
        for (int i = 1; i < n; i++) //f pode depender de todas as coordenadas simultaneamente
            K1[i] = h * F[i - 1].Eval(t, yaux[i]);

        K2[0] = t + 0.5 * h;
        for (int i = 1; i < n; i++)
            K2[i] = h * F[i - 1].Eval(t + 0.5 * h, yaux[i] + K1[i] * 0.5);

        K3[0] = t + 0.5 * h;
        for (int i = 1; i < n; i++)
            K3[i] = h * F[i - 1].Eval(t + 0.5 * h, yaux[i] + K2[i] * 0.5);

        K4[0] = t + h;
        for (int i = 1; i < n; i++)
            K4[i] = h * F[i - 1].Eval(t + h, yaux[i] + K3[i]);

        t = t + h;
        yaux[0] = t;
        yaux.operator=(yaux + (K1 + K2 * 2. + K3 * 2. + K4) * (1. / 6.));
        aux.push_back(yaux);
    }
    return aux;
}

vector<ODEpoint> ODEsolver::StormerV(const ODEpoint &y0, int n, double T, double v0)
{ //d2y/dt2 = F(t, y, dy/dt)
    double dt = (T - y0[0]) / (double)n;
    double t = y0[0];

    vector<ODEpoint> aux;
    aux.push_back(y0);

    double y11 = y0[1] - dt * v0 + dt * dt * 0.5 * F[0].Eval(t, y0[1]);
    double *y01 = new double[2];
    y01[1] = 2. * y0[1] - y11 + dt * dt * F[0].Eval(t, y0[1]);
    t += dt;
    y01[0] = t;

    ODEpoint y1(1, y01);
    aux.push_back(y1);

    for (int i = 2; i < n; i++)
    {
        t += dt;
        y1[i] = -y1[i - 2] + 2 * y1[i - 1] + dt * dt * F[0].Eval(t, y1[i - 1]);
        y1[0] = t;
        aux.push_back(y1);
    }

    return aux;
}
