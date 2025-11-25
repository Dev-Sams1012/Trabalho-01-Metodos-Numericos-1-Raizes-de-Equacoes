#ifndef EQ_CORDA_HPP
#define EQ_CORDA_HPP

#include <bits/stdc++.h>
#include <cmath>

using namespace std;
class EqCorda
{

private:
    double a3;
    double a2;
    vector<double> coeficientes;

public:
    EqCorda(double A3, double A2)
    {
        this->a3 = A3;
        this->a2 = A2;
        this->coeficientes = {3.0, -9.0 * A2, 0.0, A3};
    }

    double f(double d) const
    {
        return a3 * pow(d, 3.0) - 9.0 * a2 * d + 3.0;
    }

    double df(double d) const
    {
        return a3 * 3.0 * pow(d, 2.0) - 9.0 * a2;
    }

    double df_num(double d) const{
        double b = coeficientes[3];
        double c = b;
        for(int i = 2; i > 0; i--){
            b = b*d + coeficientes[i]; 
            c = c*d + b;
        }
        return c;
    }

    void printEqcorda(){
        printf("%.3lf*d^3 - 9*%.3lf*d + 3", a3, a2);
    }
};

#endif
