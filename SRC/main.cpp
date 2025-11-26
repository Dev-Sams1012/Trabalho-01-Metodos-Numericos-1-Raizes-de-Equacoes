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

        vector<tuple<int, int, int>> dados;

        for (int i = 0; i < n; i++)
        {
            double lambda_local;
            double a2_local;
            double a3_local;

            cout << "\nPara n: " << i + 1 << " faca:\n";
            cout << "Valor de lambda: ";
            cin >> lambda_local;
            cout << "Valor de a2: ";
            cin >> a2_local;
            cout << "Valor de a3: ";
            cin >> a3_local;

            tuple<int, int, int> tupla_local = make_tuple(lambda_local, a2_local, a3_local);
            dados.push_back(tupla_local);
        }

        cout << "Digite o valor de epsilon: ";

        double eps;
        cin >> eps;

        cout << "Digite o máximo de iterações: ";

        int maxIter;
        cin >> maxIter;

        for (vector<int>::size_type i = 0; i < dados.size(); i++)
        {
            EqCorda p = EqCorda(get<1>(dados[i]), get<2>(dados[i]));
            double lambda = get<0>(dados[i]);

            cout << "\n";
            MetodoNewton metodoNewton = MetodoNewton(maxIter, 0.5, p, eps);
            executaMetodoNewton(&metodoNewton);
            printf("\n\n\n");
            MetodoNewtonDdxNum metodoNewtonDdxNum = MetodoNewtonDdxNum(maxIter, 0.5, p, eps);
            executaMetodoNewton(&metodoNewtonDdxNum);
            printf("\n\n\n");
            MetodoNewtonFL metodoNewtonFL = MetodoNewtonFL(maxIter, 0.5, lambda, p, eps);
            executaMetodoNewton(&metodoNewtonFL);
            printf("\n\n\n");
        }

        break;
    }

    return 0;
}
