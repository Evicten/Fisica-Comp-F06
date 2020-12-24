#ifndef __FCmatrixAlgorithms__
#define __FCmatrixAlgorithms__

#include "FCmatrix.h"
#include "FCmatrixFull.h"

class FCmatrixAlgorithms{

    public:
    static void GaussElimination(FCmatrix&, Vec&, int);
    static void Swap(FCmatrix& mat, int, int); //mudar indices no vetor dos indices....  
    static void LUDecomposition(FCmatrix&, int);
    static Vec GaussSolverBanded(FCmatrix&, Vec&, int); //0 - only Gauss | 1 - substitution too
    static void LuDecompositionBanded(FCmatrix &);
};

#endif