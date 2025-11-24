#include <bits/stdc++.h>
#include "../Funcao/EqCorda.hpp"

using namespace std;

class MetodoNewton {
    protected:
    double criterio_parada;
    int itermax;
    double chute_inicial;

    public:

    MetodoNewton(double parada, int maxiter, double chute){
        criterio_parada = parada;
        itermax = maxiter;
        chute_inicial = chute;
    }

    virtual double executaMetodo() = 0;
};



