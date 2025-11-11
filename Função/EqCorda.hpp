#ifndef EQ_CORDA_HPP
#define EQ_CORDA_HPP


#include "Polinomio.hpp"
#include <cmath>

Polinomio::Polinomio(double a3, double a2){
    this->a3 = a3;
    this->a2 = a2;
}

double Polinomio::f(double d) const{
    return a3 * pow(d,3.0) - 9.0 * a2 * d + 3.0;
}

double Polinomio::df(double d) const{
    return a3 * 3.0 * pow(d,2.0) - 9.0 * a2; 
}

#endif
