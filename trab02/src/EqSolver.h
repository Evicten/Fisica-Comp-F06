#ifndef __EqSolver__
#define __EqSolver__

#include "FCmatrix.h"
#include "FCmatrixFull.h"

class EqSolver{

    public:
    EqSolver();
    EqSolver(FCmatrix&, Vec&);
    ~EqSolver();


    void SetConstants(Vec&);
    void SetMatrix(FCmatrix&);

    Vec GaussEliminationSolver(int); //1 com pivotagem, 0 sem pivot.
    Vec LUDecompositionSolver(int); //idem
    Vec JacobiIter();
    void Print(); //fiz para teste, mas pode ficar não sei

    private:
    FCmatrix* M;
    Vec b;

};

#endif