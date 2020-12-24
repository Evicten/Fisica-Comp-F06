#ifndef __FCrand__
#define __FCrand__

class FCrand{

    public:
    FCrand(int sd = 2, int a = 65, int c = 319, int m = 65537);
    
    float GetRandom();
    float GetRandom(float, float);

    float* GetRandom(int);//int N
    float* GetRandom(int, float, float); //int N, float min, float max

    //float* GetRandom(float, float); //N randoms between [0,1]




    private:
    int seed;
    int a, c, m;



};

#endif