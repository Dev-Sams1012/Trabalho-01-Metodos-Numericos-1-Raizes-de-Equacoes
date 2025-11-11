#include <bits/stdc++.h>
#include "MetodoNewton.hpp"
#include "MetodoNewtonFL.hpp"

using namespace std;

int main(){
    Polinomio p (1.0, 1.0);
    double xk  = metodoNewtonOriginalRec(0.5, p, 0.001, 0,  10000);
    cout << "Item A)\n";
    printf("xk = %lf\n", xk);
    printf("F(xk) = %lf\n", p.f(xk));

    xk = metodoNewtonFL(0.5, p, 0.001, 0.05, 10000);
    cout << "Item B)\n";
    printf("xk = %lf\n", xk);
    printf("F(xk) = %lf\n", p.f(xk));


    
    return 0;
}
