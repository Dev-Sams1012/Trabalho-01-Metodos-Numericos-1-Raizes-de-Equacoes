#include <bits/stdc++.h>
#include "Metodos/MetodoNewton.hpp"
#include "Metodos/MetodoNewtonFL.hpp"
#include <functional>

using namespace std;



void resultados(double d, EqCorda &p, double eps,string metodo){
    cout << "-----------------------------------------------------------------\n";
    printf("RESULTADOS PARA CALCULAR d USANDO O METODO %s\n", metodo.c_str());
    cout << "f(d) = ";
    p.printEqcorda();
    cout << endl;
    printf("epsilon = %lf\n", eps);
    printf("raiz aproximada = %lf\n", d);
    cout << "-----------------------------------------------------------------\n";
}

void executaMetodoNewton(function<double(double, EqCorda& , double, int)> metodo, 
                        double d, EqCorda &p, double eps, int itMax, bool usa_dfnum){
    double raiz = metodo(d , p, eps, itMax);
    if(usa_dfnum){
        resultados(raiz, p, eps, "NEWTON-RAPHSON PADRAO COM DERIVADA NUMERICA");
    }
    else{ 
        resultados(raiz, p, eps, "NEWTON-RAPHSON PADRAO");
    }
    

}

void executaMetodoNewtonFL(function<double(double, EqCorda&, double, double, int)> metodo, 
                        double d, EqCorda &p, double eps,double lbd, int itMax){
    double raiz = metodo(d , p, eps, lbd, itMax);
    resultados(raiz, p, eps, "NEWTON-RAPHSON FL");
    
}






int main()
{
    EqCorda p = EqCorda(1.0, 1.0);

    cout << "Item A)\n";
    executaMetodoNewton(metodoNewton, 0.5, p, 0.0001, 10000, false);
    printf("\n\n\n");
    cout << "Item B)\n";
    executaMetodoNewtonFL(metodoNewtonFL, 0.5, p, 0.0001, 0.05, 10000);
    printf("\n\n\n");
    cout << "Item C)\n";
    executaMetodoNewton(metodoNewtonDdxNum, 0.5, p, 0.0001, 10000, true);
    printf("\n\n\n");

    return 0;
}
