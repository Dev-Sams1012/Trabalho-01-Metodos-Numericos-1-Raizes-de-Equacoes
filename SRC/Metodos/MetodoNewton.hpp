#ifndef METODO_NEWTON_HPP
#define METODO_NEWTON_HPP

#include "MetodoNewtonAbstrato.hpp"

using namespace std;

class MetodoNewton : public MetodoNewtonAbstrato
{
public:
    MetodoNewton(int maxiter, double chute, EqCorda &eq, double parada)
        : MetodoNewtonAbstrato(maxiter, chute, eq, parada) {}

    double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        iter = 0;
        while (iter < itermax)
        {
            if (abs(p.df(d)) < 1e-6)
            {
                cout << "Derivada proxima de 0, Metodo falhou!!\n";
                return d;
            }
            double dk = d - (fx / p.df(d));
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            iter++;
        }
        cout << "Limite maximo de Iteraçoes ultrapassado!!\n";
        return d;
    }

    string nomeMetodo() const override
    {
        return "NEWTON-RAPHSON PADRAO";
    }
};

#endif