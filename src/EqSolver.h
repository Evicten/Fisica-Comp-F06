#ifndef __EqSolver__
#define __EqSolver__

#include "FCmatrix.h"
#include "FCmatrixFull.h"

class EqSolver{

    public:
    EqSolver();

    EqSolver(const FCmatrixFull&, const Vec&);


    void SetConstants(const Vec&);
    void SetMatrix(const FCmatrixFull&);

    Vec GaussEliminationSolver(int); //1 com pivotagem, 0 sem pivot.
    Vec LUDecompositionSolver(int); //idem
    Vec JacobiIter();
    void Print(); //fiz para teste, mas pode ficar não sei

    private:
    FCmatrixFull* M; //só para FCmatrixFull
    Vec b;

};

#endif