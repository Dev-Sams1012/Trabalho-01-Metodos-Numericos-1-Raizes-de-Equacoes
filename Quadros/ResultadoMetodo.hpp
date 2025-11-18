#ifndef RESULTADO_METODO_HPP
#define RESULTADO_METODO_HPP

#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Iteracao{
    int k;          // número da iteração
    double x;       // valor da aproximação
    double fx;      // valor da função
    double erro;    //erro para critério de parada

};

struct Resultado{
    double d_inicial;   // valor inicial d0
    double d_final;     // valor final de d
    double erro_final;  // erro final
    int iteracoes;      // número de iterações realizadas

    double a3;
    double a2;
    double lambda;      // lambda escolhido
    double eps;         // critério de parada

    vector<Iteracao> historico;  // histórico de todas as iterações
};


#endif