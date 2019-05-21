#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <cmath>

using namespace std;

class Operation {
    protected:
        string equation;
    public:  
        static Operation* buildFromEquation(string equation);

        inline string name() { return equation; }

        virtual float operate() = 0;

        friend class solver;

        float sum(float a, float b){
            return a+b;
        }

        float res(float a, float b){
            return a-b;
        }

        float mult(float a, float b){
            return a*b;
        }

        float div(float a, float b){
            return a/b;
        }

        float pot(float a, float b){
            return pow(a,b);
        }

};

#endif