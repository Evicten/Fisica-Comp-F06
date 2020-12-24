#ifndef __FCmatrixAlgorithms__
#define __FCmatrixAlgorithms__

#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"

class FCmatrixAlgorithms{

    public:
    static void GaussElimination(FCmatrixFull&, Vec&, int); //matrixFCFull, vec b, 0-sem pivot | 1-c/pivot   Ax = b
    static void Swap(FCmatrixFull& mat, int, int); //mudar indices no vetor dos indices....  
    static void LUDecomposition(FCmatrixFull&, int);
    static Vec GaussSolverBanded(FCmatrixBanded&, Vec&, int); //0 - only Gauss | 1 - substitution too
    static void LuDecompositionBanded(FCmatrixBanded&);
};

#endif