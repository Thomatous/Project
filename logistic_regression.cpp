#include "logistic_regression.hpp"

void train(int** bow, float* weights, int learning_rate, int entries, int words) {
    float L = 0;
    float f = 0;
    float p, J;
    short int y;
    for(int i=0 ; i < EPOCHS ; ++i) {
        for(int j=0 ; j < entries ; ++j) {
            for(int k=0 ; k < words ; ++k) {
                f += weights[k]*((float)bow[j][k]);
            }
            p = 1.0/(1.0+exp(-f));
            L += -y*(log(p)) - (1-y)*log(1-p);
        }
        J = (1.0/(float)entries)*L;

        for(int j=0 ; j < entries ; ++j) {
            weights[j] = weights[j] - (learning_rate*J);
        }
    }
}

void train(float** tf_idf, float* weights, int learning_rate, int entries, int words) {
    
}