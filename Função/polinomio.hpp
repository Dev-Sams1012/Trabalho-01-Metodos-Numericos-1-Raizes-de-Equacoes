#ifndef POLINOMIO_HPP
#define POLINOMIO_HPP

class polinomio {

private:
    double a3;
    double a2;

public:
    polinomio(double a3, double a2);

    double f(double x) const;
    double df(double x) const;
    double df_num(double x, double h) const;

};

#endif