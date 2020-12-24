#include "Motion.h"
#include <iostream>
#include <cmath>

using namespace std;

Motion::Motion(int a){
    t = new float[a];
    x = new float[a];
    N = a;
}

void Motion::SetMotion(float* v, float* T, int n){
    if(n > N)
    n = n + (N-n);

    t = T;
    x = v;
}

Motion::~Motion(){
   
    delete t;
    delete x;
}

int Motion::GetN(){
    return N;
}
float* Motion::GetTimes(){
    return t;
}
float* Motion::GetPositions(){
    return x;
}

void Motion::Print(){
    for(int i = 0; i < N; i++)
    cout << "x[" << t[i] << "]" << " = " << x[i] << " : " << i << endl;   
}
float Motion::TotalDistance(){
    float sum = 0;
    N = N - 1;
    for(int i = 0; i < N; i++)
    sum = sum + fabs(x[i+1] - x[i]);
    return sum;
}
float Motion::MeanVelocity(){
    float sum1 = Motion::TotalDistance();
    return sum1/t[N];
}
