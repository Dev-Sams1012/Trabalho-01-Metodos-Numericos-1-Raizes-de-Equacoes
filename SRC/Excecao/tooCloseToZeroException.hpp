#include <iostream>
#include <exception>

using namespace std;

class tooCloseException : public exception{
    private:
    double dx;

    public:

    tooCloseException(int deriv) : dx(deriv){}

    const char* what() const noexcept override{
        return "Derivada muito próxima de 0! Método falhou.";
    }

    int getDeriv() const{
        return dx;
    }


};