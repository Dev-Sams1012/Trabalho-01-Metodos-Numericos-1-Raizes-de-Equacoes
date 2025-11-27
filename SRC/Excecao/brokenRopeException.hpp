#ifndef BROKEN_ROPE_EXCEPTION
#define BROKEN_ROPE_EXCEPTION

#include <iostream>
#include <exception>

using namespace std;

class brokenRopeException : public exception{
    private:
    double desloc;

    public:

    brokenRopeException(double desl) : desloc(desl){}

    const char* what() const noexcept override{
        return "Corda Rompida! Método falhou.";
    }

    double getDesloc() const{
        return desloc;
    }


};

#endif