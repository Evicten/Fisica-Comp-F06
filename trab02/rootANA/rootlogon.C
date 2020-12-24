void rootlogon()
{
    printf("running my rootlogon...\n");
    gInterpreter->AddIncludePath("../src/");               // permite a ROOT saber onde estão os meus include files
    gSystem->CompileMacro("../src/Vandermonde.C", "k O");  // compila a classe point
    gSystem->CompileMacro("../src/FCmatrixFull.C", "k O"); // compila a classe line
    gSystem->CompileMacro("../src/EqSolver.C", "k O"); // compila a classe line
    gSystem->CompileMacro("../src/FCmatrix.C", "k O"); // compila a classe line
    gSystem->CompileMacro("../src/FCmatrixAlgorithms.C", "k O"); // compila a classe line
    gSystem->CompileMacro("../src/Vec.C", "k O"); // compila a classe line
}
