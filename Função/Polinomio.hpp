#ifndef POLINOMIO_HPP
#define POLINOMIO_HPP

class Polinomio {

private:
    double a3;
    double a2;

public:
    Polinomio(double a3, double a2);

    double f(double d) const;
    double df(double d) const;
    double df_num(double d, double h) const;

};

#endif