#include <iostream>
#include <exception>

using namespace std;

class maxIterException : public exception{
    private:
    int iteration;

    public:

    maxIterException(int iter) : iteration(iter){}

    const char* what() const noexcept override{
        return "Máximo de iterações ultrapassado!";
    }

    int getIter() const{
        return iteration;
    }


};