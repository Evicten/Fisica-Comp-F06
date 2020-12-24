#include <iostream>
#include <cstdlib>

using namespace std;

int*** fintv(int, int p = 0, int q = 0);
double*** fdoublev(int, int p = 0, int q = 0);

void print(auto***, int, int, int);

int main()
{
    int***a = fintv(100,50);
    double ***b = fdoublev(100, 50, 20);
    double ***c = fdoublev(100, 50);

    print(b, 100, 50, 20);

    delete []a;
    delete []b;
    delete []c;

    return 0;
}

void print(auto***as, int a, int b, int c)
{
    for(int i= 0; i< a; ++i)
    {
        for(int j = 0; j < b; ++j)
        {
            for(int k = 0; k < c; ++k)
            cout << as[i][j][k] << " " << flush;

            cout << endl;
        }
        
        cout << endl;
    }

}