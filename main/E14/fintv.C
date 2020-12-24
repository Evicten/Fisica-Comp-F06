#include <cstdlib>

int*** fintv(int n, int m, int p)
{
    int ***a;
    a = new int**[n];
    for(int i = 0; i < m; i++)
    {
        a[i] = new int*[m];
        for(int j = 0; j < p; j++)
        {
            a[i][j] = new int[p];
        }
    }
    return a;
}