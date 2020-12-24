#include <iostream>
#include "FCmatrixFull.h"
#include "FCmatrixAlgorithms.h"
#include "Vandermonde.h"
#include "TMath.h"
#include "TFile.h"
#include "TObject.h"
#include "TMultiGraph.h"
#include "TLatex.h"
#include "TCanvas.h"

using namespace std;

int main()
{
    // create a ROOT object manager
    // that will allow us to keep track of object created and use it to store them into a file and delete them
    std::vector<TObject *> ROOTmanager;

    //alinea a - função seno com modelação cos

    TF1 *alinea_a_funcao = new TF1("alinea_a", "sin(TMath::TwoPi() * x) + 0.002 * cos(100 * x)", 0, 1.5); //gerar a funcao descrita na alinea
    Vandermonde alinea_a(10, 0., 1., *alinea_a_funcao); //criar o obejto Vandermonde com as propriedades definidas no enunciado e a função acima definida

    cout << alinea_a.GetCoefficients() << endl; //cout dos coeficientes determinados no construtor do Vandermonde

    TGraph *GraphPoints = &alinea_a.GetGraphPoints(); //grafico gerado pelos 10 pontos determinados no construtor 
    ROOTmanager.emplace_back(GraphPoints); //colocar o grafico no root

    TF1 *funcPoly = &alinea_a.GetPolyFunc(); //função polinomial determinada pela interpolação de Vandermonde com base nos 10 pontos
    ROOTmanager.emplace_back(funcPoly); //colocar a funcao no root

    TCanvas *a_canvas = new TCanvas("cPoly", "cPoly", 0, 0, 500, 500); //inicializar o canvas onde serao desenhados grafico e funcao juntos
    GraphPoints->Draw("AP"); //desenhar o grafico com as opcoes pretendidas
    funcPoly->Draw("same"); //desenhar funcao por cima

    ROOTmanager.emplace_back(a_canvas); //colocar canvas cpoly no root

    //alinea b -determinaçao de erros
    int n = 0; //numero de pontos - inicializar variavel
    double *n_g = new double[15]; //inicializar vetor para receber 15 valores de n
    double *error = new double[15]; //inicializar vetor para recebr os 15 valores de n correspondentes

    for (int i = 0; i < 15; i++) //iterar para determinar erros em funcao de n
    {
        n = 4 * (1 + i); //iteração de n como pretendido no enunciado
        Vandermonde alinea_b(n, 0., 1., *alinea_a_funcao); //gerar o Vandermonde com a mesma funcao da alinea a, mas com este numero de pontos n
        n_g[i] = n; //atribuit valor de n
        error[i] = alinea_b.GetCoefError(); //determinar erro usando funcao de Vandermonde
    }


//gerar graficos e canvas:
    TGraph *gErrors = new TGraph(15, n_g, error);
    gErrors->SetMarkerStyle(21);
    gErrors->SetMarkerColor(39);
    gErrors->SetMarkerSize(2);
    gErrors->SetNameTitle("gErros");
    gErrors->SetLineStyle(kSolid);
    gErrors->SetLineColor(kGreen + 2);
    gErrors->SetLineWidth(2);
    TCanvas *canvas_err = new TCanvas("gErrors", "gErrors", 0, 0, 500, 500);
    gPad->SetLogy();
    gErrors->Draw("AP"); //não colocámos a opção L para linha porque quando o fazíamos, o gráfico no root não abria... só assim conseguimos visualizar os pontos em escala logarítmica 

//colocar na root
    ROOTmanager.emplace_back(canvas_err);


    //alinea c
    
    FCmatrixFull inverseMatrix;
    cout << alinea_a.GetMatrix() << endl; //cout da matriz dos coeficientes
    cout << "--------" << endl;
    alinea_a.GetInverseMatrix(inverseMatrix); //calculo da matriz inversa
    cout << inverseMatrix << endl; //cout da matriz inversa

    TFile *file = new TFile("../trab02.root", "RECREATE"); //criar ficheiro na pasta trab02

    for (auto x : ROOTmanager) //escrever
        x->Write();

    file->Close();


    return 1;
}