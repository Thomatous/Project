#ifndef _LOGISTIC_REGRESSION_
#define _LOGISTIC_REGRESSION_

#include <iostream>
#include <cmath>
#include "hashtable.hpp"
#include "sparse_matrix.hpp"
#include <fstream>

#define EPOCHS 5
#define THRESHOLD 0.05
#define LEARNING_RATE 0.3

class LR{
public:
    float prevL, L, J;
    const unsigned int weights_size;
    float* weights;
    float* thetaJ;
    unsigned int pred_counter, pred_threshold_counter;
    unsigned int val_counter, val_threshold_counter;
    LR(unsigned int);
    ~LR();

    // void gradient_descent(int*, int*, short int);
    void gradient_descent(int, int, short int, SM*);
    void train(SM*, std::string*, unsigned int, HashTable*);
    // void train(SM*, std::string*, unsigned int, float, HashTable*);
    void predict(SM*, std::string*, unsigned int, HashTable*);
    void validate(SM*, std::string*, unsigned int , HashTable*);
    void validate_unknown(SM*, Clique*, Clique*);
};

#endif