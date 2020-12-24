#ifndef __Motion__
#define __Motion__

class Motion {
    public:
    Motion(int N = 0);
    virtual ~Motion();

    void SetMotion(float* t, float* x, int);

    int GetN();
    float* GetTimes();
    float* GetPositions();

    virtual void Print();
    virtual float TotalDistance();
    virtual float MeanVelocity();

    protected:
    int N;
    float* t;
    float* x;
};

#endif