#ifndef EQ_CORDA_HPP
#define EQ_CORDA_HPP

#include <cmath>

class EqCorda
{

private:
    double a3;
    double a2;

public:
    EqCorda(double A3, double A2)
    {
        this->a3 = A3;
        this->a2 = A2;
    }

    double f(double d) const
    {
        return a3 * pow(d, 3.0) - 9.0 * a2 * d + 3.0;
    }

    double df(double d) const
    {
        return a3 * 3.0 * pow(d, 2.0) - 9.0 * a2;
    }

    double df_num(double d, double h) const{
        return (f(d + h) - f(d)) / h;
    }

    void printEqcorda(){
        printf("%.3lf*d^3 - 9*%.3lf*d + 3", a3, a2);
    }
};

#endif
