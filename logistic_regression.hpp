#ifndef _LOGISTIC_REGRESSION_
#define _LOGISTIC_REGRESSION_

#include <iostream>
#include <cmath>
#include "hashtable.hpp"

#define EPOCHS 100

class LR{
public:
    float L, J;
    const unsigned int weights_size;
    float* weights;
    LR(unsigned int);
    ~LR();

    void gradient_descent(int*, int*, float);
    void gradient_descent(float*, float*, float);
    void train(float**, std::string*, unsigned int, float, HashTable*);
    void predict();
};

#endif