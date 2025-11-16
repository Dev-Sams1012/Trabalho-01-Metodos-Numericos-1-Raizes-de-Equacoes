#include <bits/stdc++.h>
#include "Métodos/MetodoNewton.hpp"
#include "Métodos/MetodoNewtonFL.hpp"

using namespace std;

int main()
{
    EqCorda p = EqCorda(1.0, 1.0);
    double xk = metodoNewton(0.5, p, 0.0001, 10000);

    cout << "Item A)\n";
    printf("xk = %lf\n", xk);
    printf("F(xk) = %lf\n", p.f(xk));

    xk = metodoNewtonFL(0.5, p, 0.0001, 0.05, 10000);

    cout << "Item B)\n";
    printf("xk = %lf\n", xk);
    printf("F(xk) = %lf\n", p.f(xk));

    xk = metodoNewtonDdxNum(0.5, p, 0.0001, 10000);

    cout << "Item C)\n";
    printf("xk = %lf\n", xk);
    printf("F(xk) = %lf\n", p.f(xk));

    return 0;
}
