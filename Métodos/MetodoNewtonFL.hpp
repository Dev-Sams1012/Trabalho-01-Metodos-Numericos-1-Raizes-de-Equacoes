#ifndef METODO_NEWTON_F_L_HPP
#define METODO_NEWTON_F_L_HPP
#include <bits/stdc++.h>
#include "../Função/EqCorda.hpp"

using namespace std;

double metodoNewtonFL(double d, EqCorda &p, double eps, double lbd, int itMax)
{
    double fx = p.f(d);
    if (abs(fx) < eps)
        return d;
    int k = 1;
    double FL = p.df(d);
    while (k < itMax)
    {
        double dk = d - (fx / FL);
        fx = p.f(dk);
        if (abs(d - dk) < eps || abs(fx) < eps)
            return dk;
        d = dk;
        if (abs(p.df(d)) >= lbd)
            FL = p.df(d);
        k++;
    }
    cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
    return d;
}

#endif