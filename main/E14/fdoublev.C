#include <cstdlib>

double*** fdoublev(int n, int m, int p)
{
    double ***a;
    a = new double**[n];
    for(int i = 0; i < m; i++)
    {
        a[i] = new double*[m];
        for(int j = 0; j < p; j++)
        {
            a[i][j] = new double[p];
        }
    }
    return a;
}