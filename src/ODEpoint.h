#ifndef __ODEpoint__
#define __ODEpoint__


class ODEpoint{

    public:

    ODEpoint(int fdim = 0, const double* xi = nullptr); //fdim - variaveis dependesntes de f(t, y)
    ODEpoint(const ODEpoint&);
    ~ODEpoint();

    int Ndim() const {return ndim;};

    double T() const {return x[0];};
    double X(int i) const {return x[i+1];};
    double* GetArray() {return x;};

    ODEpoint operator*(double) const;
    ODEpoint operator+(const ODEpoint&) const;
    ODEpoint operator-(const ODEpoint&) const;

    const ODEpoint& operator=(const ODEpoint&);

    const double operator[](int) const;
    double& operator[](int);

    private:
    int ndim; // nb of dependent variables
    double *x; // independent variable(t) + dependent variable ==(ndim+1)

};

#endif