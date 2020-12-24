#include <iostream>

using namespace std;

int main(){

    double a = 4.;
    double* v = new double[1000];
    for(int i = 0; i < 1000; ++i)
    v[i] = 10.;

    cout << "hello" << endl;
    cout << "vhvh " << v[200] << endl;

    return 1;
}