#ifndef _LOGISTIC_REGRESSION_
#define _LOGISTIC_REGRESSION_

#include <iostream>
#include <cmath>
#include "hashtable.hpp"

#define EPOCHS 5

class LR{
public:
    float L, J;
    const unsigned int weights_size;
    float* weights;
    float* thetaJ;
    LR(unsigned int);
    ~LR();

    void gradient_descent(int*, int*, short int);
    void gradient_descent(float*, float*, short int);
    void train(float**, std::string*, unsigned int, float, HashTable*);
    void train(int**, std::string*, unsigned int, float, HashTable*);
    void predict();
};

#endif