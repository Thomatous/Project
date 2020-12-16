#include "logistic_regression.hpp"

LR::LR(unsigned int w_size): weights_size(w_size) {
    weights = new float[w_size];
    for(int i=0 ; i < w_size ; ++i) {
        weights[i] = 0;
    }
}

LR::~LR() {
    for(int i=0 ; i < weights_size ; ++i) {
        std::cout << weights[i] << "\n";
    }
    delete[] weights;
}

void LR::gradient_descent(int* bow1, int* bow2, float learning_rate) {
    float f = 0;
    float p;
    L = 0;
    short int y;
    for(int i=0 ; i < weights_size/2 ; ++i) {
        f += weights[i]*((float)bow1[i]);
        f += weights[i+weights_size]*((float)bow2[i]);
    }
    p = 1.0/(1.0+exp(-f));
    L += -y*(log(p)) - (1-y)*log(1-p);
}

void LR::gradient_descent(float* tf_idf1, float* tf_idf2, float learning_rate) {
    float f = 0;
    float p;
    L = 0;
    short int y;
    for(int i=0 ; i < weights_size/2 ; ++i) {
        f += weights[i]*((float)tf_idf1[i]);
        f += weights[i+weights_size]*((float)tf_idf2[i]);
    }
    p = 1.0/(1.0+exp(-f));
    L += -y*(log(p)) - (1-y)*log(1-p);
}

void LR::train(float** tf_idf, std::string* train, unsigned int train_size, float learning_rate, HashTable* ht) {
    Entry *e1, *e2;
    std::string url1, url2, label_str;
    short int label;
    std::string word, site1, id1, site2, id2;
    size_t first_slash;
    for(int j=0 ; j < EPOCHS ; ++j) {
        for(int i=0 ; i < train_size ; ++i) {
            std::stringstream line_stringstream(train[i]);
            for(int j=0 ; j < 3 ; ++j  ) {
                if(j == 0) {
                    getline(line_stringstream, url1 , ',');
                    first_slash = url1.find_first_of('/');
                    site1 = url1.substr(0,first_slash);
                    id1 = url1.substr(first_slash+2);
                }
                else if(j == 1) {
                    getline(line_stringstream, url2, ',');
                    first_slash = url2.find_first_of('/');
                    site2 = url2.substr(0,first_slash);
                    id2 = url2.substr(first_slash+2);
                }
                else if(j == 2) {
                    getline(line_stringstream, label_str, ',');
                    label = atoi(label_str.c_str());       
                }
            }
            e1 = ht->search(hash_value_calculator(site1, id1));
            e2 = ht->search(hash_value_calculator(site2, id2));

            gradient_descent(tf_idf[e1->loc], tf_idf[e2->loc], learning_rate);

        }

        J = (1.0/(float)train_size)*L;

        for(int k=0 ; k < weights_size ; ++k) {
            weights[k] = weights[k] - (learning_rate*J);
        }
    }

}

