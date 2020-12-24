#include "IntegratorMC.h"
#include "TRandom.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

IntegratorMC::~IntegratorMC()
{
    if (f2D)
        delete f2D;
}

void IntegratorMC::SetIntegrandFunction(const TF1 *func1)
{
    TF1 faux(*func1);
    f = &faux;

    delete func1;
}

void IntegratorMC::GetRange2D(double &xmin, double &xmax, double &ymin, double &ymax)
{
    f2D->GetRange(xmin, xmax, ymin, ymax);
    cout << "xmin: " << xmin << " ymax: " << ymax << " xmax: " << xmax <<  endl;
    cout << __PRETTY_FUNCTION__ << endl;
}

void IntegratorMC::IntegralMC(int N, double &result, double &error)
{
    double xmin, xmax;
    GetRange(xmin, xmax);
    double inter = xmax - xmin;
    double sum = 0.;
    double sum2 = 0.;
    double fi;

    for (int i = 0; i < N; i++)
    {
        double x = xmin + inter * gRandom->Uniform();
        fi = Eval(x);
        sum = sum + fi;

        sum2 = sum2 + fi * fi;
    }

    double avgfi = sum / ((double)N);
    result = avgfi * inter;

    double error1 = sum2 / ((double)N) - avgfi * avgfi;

    error = inter * sqrt(error1) / sqrt((double)N);
}

void IntegratorMC::IntegralMCIS(int &N, double &result, double &error, const TF1 *pdf, const TF1 *xy)
{ //in a pdf  I have x(y), y generates a random double between 0 and 1
    double xmin, xmax;
    GetRange(xmin, xmax);
    bool bN = true;

    if(error > 0.){
        N = 0;
        bN = false;
    }

    double Fsum = 0.;
    double Fsum2 = 0.;

    int count = 0;
    double error_t = 1.;

    gRandom->SetSeed(0);
    TF1 faux(*pdf);
    
    while((bN && count < N) || (!bN && error_t < error)){

        if(count == 0){
            cout << "valor integral: "<< faux.Integral(xmin, xmax) << endl;
        }

        double y = gRandom->Uniform();
        double x = xy->Eval(y);

        double ratio = Eval(x)/pdf->Eval(x);

        Fsum+= ratio;
        Fsum2+= ratio*ratio;

        double Fmean = Fsum/count;
        double Fmean2 = Fsum2/count;
        double variance = Fmean2 - Fmean*Fmean;

        error_t = sqrt(variance/count);
        count = count + 1;
    }

    N = count;
    error = error_t;
    result = Fsum/N;
    
    /*  my code
    double xmin, xmax;
    GetRange(xmin, xmax);

    double inter = xmax - xmin;
    double sum = 0.;
    double sum2 = 0.;
    double fi, x, y, px, ratio;

    for (int i = 0; i < N; i++)
    {
        y = gRandom->Uniform(); //y
        x = xy->Eval(y);        //x(y)
        px = pdf->Eval(x);      //p(x(y))
        fi = Eval(x);           //f(x(y))
        ratio = fi / px;
        sum = sum + ratio;
        sum2 = sum2 + ratio * ratio;
    }

    double avgfi = sum / ((double)N);
    result = avgfi;

    double error1 = sum2 / ((double)N) - avgfi * avgfi;
    error = sqrt(error1/(double)N);
    */
}

void IntegratorMC::IntegralMCAR(int N, double &result, double &error)
{ //basic one uses uniform pdf
    double xmin, xmax;
    GetRange(xmin, xmax);

    double inter = xmax - xmin;
    double maxx = f->GetMaximumX();
    double fmax = Eval(maxx);
    cout << "valor fmax: " << fmax << endl;

    double xR, fR;
    int n = 0; //favorable events

    for (int i = 0; i < N; i++)
    {

        xR = xmin + inter * gRandom->Uniform();
        fR = fmax * gRandom->Uniform();

        if (fR <= Eval(xR))
            n = n + 1;
    }
    double NR = (double)n;
    double NN = (double)N;
    double subRes = inter * fmax / NN;

    result = subRes * NR;
    error = subRes * sqrt(NR * (1. - NR / NN));
}

void IntegratorMC::IntegralMCAR(int N, double &result, double &error, const TF1 *pdfq, const TF1 *qr, const TF1 *xy)
{ //uses a pdf given by the user
    double xmin, xmax;
    GetRange(xmin, xmax);

    TF1 faux(*qr);

    double inter = xmax - xmin;
    double Intq = faux.Integral(xmin, xmax);
    double y;
    double xR, fR;
    int n = 0; //favorable events
    double qxR, ratio;
    double uR;
    int a = 0;

    for (int i = 0; i < N; i++)
    {
        y = gRandom->Uniform(); //y de [0,1]
        xR = xy->Eval(y);       //x(y)
        fR = Eval(xR);          //f(x(y))
        qxR = qr->Eval(xR);     //q(x(y))
        ratio = fR / qxR;
        uR = gRandom->Uniform();
        if (uR <= ratio)
            n += 1;
    }
    double NR = (double)n;
    double NN = (double)N;

    double subRes = Intq / NN;
    result = subRes * NR;

    error = subRes * sqrt(NR * (1. - NR / NN));
}

void IntegratorMC::IntegralMCBF(int N, double &result)
{
    double xmin, xmax, ymin, ymax;
    GetRange2D(xmin, xmax, ymin, ymax);
    //cout << "xmin: " << xmin << " xmax: " << xmax << " ymin: " << ymin << " ymax: " << ymax << endl;
    double interx = xmax - xmin;
    double intery = ymax - ymin;
    //cout << "interx: " << interx << " intery: " << intery << endl;
    double xr1, xr2;
    double sum = 0.;
    double fi;

    for (int i = 0; i < N; i++)
    {
        gRandom->SetSeed(0);
        xr1 = xmin + interx * gRandom->Uniform();
        gRandom->SetSeed(19);
        xr2 = xmin + interx * gRandom->Uniform();

        fi = f2D->Eval(xr1, xr2);
        sum = sum + fi;
    }

    result = interx * intery * sum / ((double)N);
}
