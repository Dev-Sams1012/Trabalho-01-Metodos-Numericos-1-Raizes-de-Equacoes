#ifndef METODO_NEWTON_FL_HPP
#define METODO_NEWTON_FL_HPP

#include <bits/stdc++.h>
#include "../Funcao/EqCorda.hpp"

using namespace std;

class MetodoNewtonFL : public MetodoNewtonAbstrato
{
protected:
    double lbd;

public:
    MetodoNewtonFL(int maxiter, double chute, double fator, EqCorda &eq, double parada)
        : MetodoNewtonAbstrato(maxiter, chute, eq, parada), lbd(fator) {}

    double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        int k = 1;
        double FL = p.df(d);
        while (k < itermax)
        {
            double dk = d - (fx / FL);
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            if (abs(p.df(d)) >= lbd)
                FL = p.df(d);
            k++;
        }
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return d;
    }

    string nomeMetodo() const override
    {
        return "NEWTON-RAPHSON FL";
    }

    string infoExtra() const override
    {
        return "lambda = " + to_string(lbd);
    }
};

#endif