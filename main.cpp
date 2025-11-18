#include <bits/stdc++.h>
#include "Metodos/MetodoNewton.hpp"
#include "Metodos/MetodoNewtonFL.hpp"
#include <functional>
#include <tuple>

using namespace std;

void resultados(double d, EqCorda &p, double eps, string metodo)
{
    cout << "-----------------------------------------------------------------\n";
    printf("RESULTADOS PARA CALCULAR d USANDO O METODO %s\n", metodo.c_str());
    cout << "f(d) = ";
    p.printEqcorda();
    cout << endl;
    printf("epsilon = %lf\n", eps);
    printf("raiz aproximada = %lf\n", d);
    cout << "-----------------------------------------------------------------\n";
}

void executaMetodoNewton(function<double(double, EqCorda &, double, int)> metodo,
                         double d, EqCorda &p, double eps, int itMax, bool usa_dfnum)
{
    double raiz = metodo(d, p, eps, itMax);
    if (usa_dfnum)
    {
        resultados(raiz, p, eps, "NEWTON-RAPHSON PADRAO COM DERIVADA NUMERICA");
    }
    else
    {
        resultados(raiz, p, eps, "NEWTON-RAPHSON PADRAO");
    }
}

void executaMetodoNewtonFL(function<double(double, EqCorda &, double, double, int)> metodo,
                           double d, EqCorda &p, double eps, double lbd, int itMax)
{
    double raiz = metodo(d, p, eps, lbd, itMax);
    resultados(raiz, p, eps, "NEWTON-RAPHSON FL");
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

        for (vector<int>::size_type i = 0; i < dados.size(); i++)
        {
            EqCorda p = EqCorda(get<1>(dados[i]), get<2>(dados[i]));

            cout << "\n";
            executaMetodoNewton(metodoNewton, 0.5, p, 0.0001, 10000, false);
            printf("\n\n\n");
            cout << "\n";
            executaMetodoNewtonFL(metodoNewtonFL, 0.5, p, 0.0001, get<0>(dados[i]), 10000);
            printf("\n\n\n");
            cout << "\n";
            executaMetodoNewton(metodoNewtonDdxNum, 0.5, p, 0.0001, 10000, true);
            printf("\n\n\n");
        }

        break;
    }

    return 0;
}
