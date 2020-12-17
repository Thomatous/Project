#ifndef _LOGISTIC_REGRESSION_
#define _LOGISTIC_REGRESSION_

#include <iostream>
#include <cmath>
#include "hashtable.hpp"
#include "sparse_matrix.hpp"

#define EPOCHS 50

class LR{
public:
    float L, J;
    const unsigned int weights_size;
    float* weights;
    float* thetaJ;
    unsigned int pred_counter;
    LR(unsigned int);
    ~LR();

    // void gradient_descent(int*, int*, short int);
    void gradient_descent(int, int, short int, SM*);
    void train(SM*, std::string*, unsigned int, float, HashTable*);
    // void train(SM*, std::string*, unsigned int, float, HashTable*);
    void predict(SM*, std::string*, unsigned int, HashTable*);
};

#endif