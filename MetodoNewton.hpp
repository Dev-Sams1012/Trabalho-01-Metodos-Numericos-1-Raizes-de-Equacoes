#ifndef METODO_NEWTON_HPP
#define METODO_NEWTON_HPP
#include <bits/stdc++.h>
#include "Função/EqCorda.hpp"

using namespace std;



// NEWTON ORIGINAL ITERATIVO

double metodoNewtonOriginal(double d,Polinomio &p, double eps,int itMax){
    double fx = p.f(d);
    if(abs(fx)<eps) return d;
    int k = 1;
    while(k<itMax){
        if(abs(p.df(d))<1e-6){
            cout << "Derivada proxima de 0, Metodo falhou!!\n";
            return d;
        }
        double dk = d - (fx/p.df(d));
        fx = p.f(dk);
        if(abs(d - dk)<eps || abs(fx)<eps) return dk;
        d = dk;
        k++;
    }
    cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
    return d;
}



// NEWTON ORIGINAL RECURSIVO

double metodoNewtonOriginalRec(double d,Polinomio &p, double eps, int k, int itMax){
    double fx = p.f(d);
    if(abs(fx)<eps) return d;
    double dk = d - (fx/p.df(d));
    if(abs(d - dk)<eps) return dk;
    else if(k>=itMax){
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return dk;
    }
    else return metodoNewtonOriginalRec(dk, p, eps, k+1, itMax);
}

#endif