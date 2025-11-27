#ifndef METODO_NEWTON_DDX_NUM_HPP
#define METODO_NEWTON_DDX_NUM_HPP

#include "MetodoNewtonAbstrato.hpp"
#include "Excecao\maxIterException.hpp"
#include "Excecao\tooCloseToZeroException.hpp"

using namespace std;

class MetodoNewtonDdxNum : public MetodoNewtonAbstrato
{
public:
    MetodoNewtonDdxNum(int maxiter, double chute, EqCorda &eq, double parada)
        : MetodoNewtonAbstrato(maxiter, chute, eq, parada) {}

    double executaMetodo() override
    {
        double fx = p.f(d);
        if (abs(fx) < eps)
            return d;
        int k = 1;
        while (k < itermax)
        {
            if (abs(p.df_num(d)) < 1e-6)
            {
                throw tooCloseException(d);
            }
            double dk = d - (fx / p.df_num(d));
            fx = p.f(dk);
            if (criterioParada(dk, d))
                return dk;
            d = dk;
            k++;
        }
        if (k >= itermax){
            throw maxIterException(k);
        }
    }

    string nomeMetodo() const override
    {
        return "NEWTON-RAPHSON COM DERIVADA NUMERICA";
    }
};

#endif