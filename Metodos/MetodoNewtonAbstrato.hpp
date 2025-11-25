#ifndef METODO_NEWTON_ABSTRATO_HPP
#define METODO_NEWTON_ABSTRATO_HPP

#include <bits/stdc++.h>
#include "../Funcao/EqCorda.hpp"

using namespace std;

class MetodoNewtonAbstrato
{
protected:
    bool goodEnough = false;
    int itermax;
    double eps;
    double d;
    EqCorda &p;

public:
    MetodoNewtonAbstrato(int maxiter, double chute, EqCorda &eq, double parada)
        : goodEnough(false), itermax(maxiter),eps(parada), d(chute), p(eq){}

    virtual bool criterioParada(double atual, double anterior) const
    {
        return abs(atual - anterior) < eps and abs(p.f(atual)) < eps;
    }

    virtual double executaMetodo() = 0;

    virtual string nomeMetodo() const = 0;

    virtual string infoExtra() const
    {
        return "";
    }

    double getEps() const
    {
        return eps;
    }

    EqCorda &getEq() const
    {
        return p;
    }
};

#endif