#include <bits/stdc++.h>
#include "Metodos/MetodoNewton.hpp"
#include "Metodos/MetodoNewtonDdxNum.hpp"
#include "Metodos/MetodoNewtonFL.hpp"
#include <functional>
#include <tuple>

using namespace std;

void resultados(double d, EqCorda &p, double eps, string metodo, string extra)
{
    cout << "-----------------------------------------------------------------\n";
    cout << "RESULTADOS PARA CALCULAR d USANDO O METODO " << metodo << "\n";
    cout << "f(d) = ";
    p.printEqcorda();
    cout << endl;

    if (!extra.empty())
        cout << extra << endl;

    printf("epsilon = %lf\n", eps);
    printf("raiz aproximada = %lf\n", d);
    cout << "-----------------------------------------------------------------\n";
}

void executaMetodoNewton(MetodoNewtonAbstrato *metodo)
{
    double raiz = metodo->executaMetodo();

    resultados(
        raiz,
        metodo->getEq(),
        metodo->getEps(),
        metodo->nomeMetodo(),
        metodo->infoExtra()
    );
}

int main()
{

    while (true)
    {
        cout << "Atividade 03 - Metodos Numericos 1 - Oscilacao de uma Corda Elastica.\n";
        cout << "Digite o numero de opcoes ( n ): ";

        int n;
        cin >> n;

        vector<double> dados;

        for (int i = 0; i < n; i++)
        {
            double lambda_local;

            cout << "\nPara n: " << i + 1 << " faca:\n";
            cout << "Valor de lambda: ";
            cin >> lambda_local;

            dados.push_back(lambda_local);
        }

        cout << "\nInforme os valores de A3 e A2:\n";

        double a3, a2;
        cout << "A3: ";
        cin >> a3;
        cout << "\nA2: ";
        cin >> a2;

        cout << "\nDigite o valor de epsilon: ";

        double eps;
        cin >> eps;

        cout << "\nDigite o maximo de iteracoes: ";

        int maxIter;
        cin >> maxIter;

        //Execucao dos metodos

        EqCorda p = EqCorda(a3, a2);
        cout << "\n";
            MetodoNewton metodoNewton = MetodoNewton(maxIter, 0.5, p, eps);
            executaMetodoNewton(&metodoNewton);
            cout << "O numero de iteracoes foi: " << metodoNewton.getIter() << "\n";
            printf("\n\n\n");
            MetodoNewtonDdxNum metodoNewtonDdxNum = MetodoNewtonDdxNum(maxIter, 0.5, p, eps);
            executaMetodoNewton(&metodoNewtonDdxNum);
            cout << "O numero de iteracoes foi: " << metodoNewtonDdxNum.getIter() << "\n";
            printf("\n\n\n");

        for (vector<int>::size_type i = 0; i < dados.size(); i++)
        {
            double lambda = dados[i];

            MetodoNewtonFL metodoNewtonFL = MetodoNewtonFL(maxIter, 0.5, lambda, p, eps);
            executaMetodoNewton(&metodoNewtonFL);
            cout << "O numero de iteracoes foi: " << metodoNewtonFL.getIter() << "\n";
            printf("\n\n\n");
        }

        break;
    }

    return 0;
}
