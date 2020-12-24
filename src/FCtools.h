#ifndef __FCtools__
#define __FCtools__

#include "Vec.h"

using namespace std;

class FCtools {
    public:
    static vector<string> ReadFile2String(string);
    static vector<Vec> ReadFile2Vec(string);
    static Vec* ReadFile2Vecp(string, int&);

    static vector<string> split(string, string);

};

#endif