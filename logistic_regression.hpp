#ifndef _LOGISTIC_REGRESSION_
#define _LOGISTIC_REGRESSION_

#include <iostream>
#include <cmath>
#include "hashtable.hpp"
#include "sparse_matrix.hpp"
#include <fstream>
#include "job_scheduler.hpp"
#include "thread"

#define EPOCHS 5
#define THRESHOLD 0.1
// medium: bs 1 lr 0.3 , bs 16 lr 0.3
// large:  bs 1 lr     , bs 16 lr 8
#define LEARNING_RATE 5
#define BATCH_SIZE 1024

class JobScheduler;

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
    void train(SM*, std::string*, unsigned int, HashTable*, JobScheduler*);
    // void train(SM*, std::string*, unsigned int, float, HashTable*);
    void predict(SM*, std::string*, unsigned int, HashTable*);
    float predict(SM* files, Entry* e1, Entry* e2);
    void validate(SM*, std::string*, unsigned int , HashTable*);
    void validate_unknown(SM*, Clique*, Clique*);
};

#endif