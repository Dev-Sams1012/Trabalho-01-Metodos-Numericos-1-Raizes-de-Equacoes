#ifndef RESULTADO_METODO_HPP
#define RESULTADO_METODO_HPP

#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Iteracao
{
    int k;       // número da iteração
    double x;    // valor da aproximação
    double fx;   // valor da função
    double erro; // erro para critério de parada
};

struct Resultado
{
    double d_inicial;  // valor inicial d0
    double d_final;    // valor final de d
    double erro_final; // erro final
    int iteracoes;     // número de iterações realizadas

    double a3;
    double a2;
    double lambda; // lambda escolhido
    double eps;    // critério de parada

    vector<Iteracao> historico; // histórico de todas as iterações
};

struct LinhaQuadroResposta
{
    string metodo; // nome do método
    double a3;
    double a2;
    double lambda;
    double d0;
    double d_final;
    double erro_final;
    int iteracoes;
    string estado; // seguro ou nao
};

// Função para gerar quadro de resposta
/*
vector<LinhaQuadroResposta> montarQuadroResposta(const vector<Resultado> &resultados)
{
    vector<LinhaQuadroResposta> tabela;

    for (const auto &r : resultados)
    {
        LinhaQuadroResposta L;
        L.metodo = (r.lambda == 0 ? "Newton" : "Newton FL");
        L.a3 = r.a3;
        L.a2 = r.a2;
        L.lambda = r.lambda;
        L.d0 = r.d_inicial;
        L.d_final = r.d_final;
        L.erro_final = r.erro_final;
        L.iteracoes = r.iteracoes;
        L.estado = (r.d_final > 0.3 ? "QUEBRA" : "SEGURO");

        tabela.push_back(L);
    }

    return tabela;
}
Em progresso, para lidar com nomeação correta dos métodos e outras peculiaridades.*/

struct LinhaQuadroComparativo
{
    int k;           // iteracao
    double x_newton; // raiz aproximada
    double erro_newton;

    double x_newtonFL;
    double erro_newtonFL;

    double x_newtonNum;
    double erro_newtonNum;
};

// Função para gerar quadro comparativo
vector<LinhaQuadroComparativo>
montarQuadroComparativo(const Resultado &N, const Resultado &FL, const Resultado &Num)
{
    vector<LinhaQuadroComparativo> tabela;
    int numIterNewton = N.historico.size();
    int numIterNewtonFL = FL.historico.size();
    int numIterNewtonNum = Num.historico.size();

    int maxIter = max(max(numIterNewton, numIterNewtonFL), numIterNewtonNum);

    for (int i = 0; i < maxIter; i++)
    {
        LinhaQuadroComparativo L;

        L.k = i;

        // Newton
        if (i < numIterNewton)
        {
            L.x_newton = N.historico[i].x;
            L.erro_newton = N.historico[i].erro;
        }
        else
        {
            L.x_newton = NAN;
            L.erro_newton = NAN;
        }

        // Newton FL
        if (i < numIterNewtonFL)
        {
            L.x_newtonFL = FL.historico[i].x;
            L.erro_newtonFL = FL.historico[i].erro;
        }
        else
        {
            L.x_newtonFL = NAN;
            L.erro_newtonFL = NAN;
        }

        // Newton Numérico
        if (i < numIterNewtonNum)
        {
            L.x_newtonNum = Num.historico[i].x;
            L.erro_newtonNum = Num.historico[i].erro;
        }
        else
        {
            L.x_newtonNum = NAN;
            L.erro_newtonNum = NAN;
        }

        tabela.push_back(L);
    }

    return tabela;
}

#endif