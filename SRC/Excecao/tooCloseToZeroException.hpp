#ifndef TOO_CLOSE_EXCEPTION
#define TOO_CLOSE_EXCEPTION

#include <iostream>
#include <exception>

using namespace std;

class tooCloseException : public exception{
    private:
    double dx;

    public:

    tooCloseException(double deriv) : dx(deriv){}

    const char* what() const noexcept override{
        return "Derivada muito próxima de 0! Método falhou.";
    }

    double getDeriv() const{
        return dx;
    }


};

#endif