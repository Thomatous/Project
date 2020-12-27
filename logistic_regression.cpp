#include "logistic_regression.hpp"

LR::LR(unsigned int w_size): weights_size(w_size), pred_counter(0) {
    prevL = INTMAX_MAX;
    pred_counter = 0;
    pred_threshold_counter = 0;
    val_counter = 0;
    val_threshold_counter = 0;
    weights = new float[w_size];
    thetaJ = new float[w_size];
    for(int i=0 ; i < w_size ; ++i) {
        weights[i] = 0;
        thetaJ[i] = 0;
    }
}

LR::~LR() {
//     for(int i=0 ; i < weights_size ; ++i) {
//         std::cout << weights[i] << "\n";
//     }
    delete[] weights;
    delete[] thetaJ;
}

void LR::gradient_descent(int e1, int e2, short int y, SM* files) {
    float f = 0;
    float p;
    float x[weights_size];
    float tf_idf1[weights_size/2] = {0};
    float tf_idf2[weights_size/2] = {0};
    files->get_tfidf_vector(e1, tf_idf1);
    files->get_tfidf_vector(e2, tf_idf2);

    for(int i=0 ; i < weights_size ; ++i) {
        if(i < weights_size/2) {
            x[i] = tf_idf1[i];
            x[i+weights_size/2] = tf_idf2[i];
        }
        f += weights[i]*((float)x[i]);
    }
    p = 1.0/(1.0+exp(-f));
    L += -y*(log(p)) - (1-y)*log(1-p);
    for(int j=0 ; j < weights_size ; ++j) {
        thetaJ[j] += (p*(1-p) - y)*x[j];
    }
}

void LR::train(SM* files, std::string* train, unsigned int train_size, float learning_rate, HashTable* ht) {
    std::cout << "Started training..." << std::endl;
    Entry *e1, *e2;
    std::string url1, url2, label_str;
    short int label;
    std::string word, site1, id1, site2, id2;
    size_t first_slash;
    for(int j=0 ; j < EPOCHS ; ++j) {
        std::cout << "Iteration: " << j+1 << ", L = " << std::flush;
        for(int i=0 ; i < train_size ; ++i) {
            std::stringstream line_stringstream(train[i]);
            prevL = L;
            L = 0;
            for(int k=0 ; k < weights_size ; ++k) {
                thetaJ[k] = 0;
            }
            for(int k=0 ; k < 3 ; ++k  ) {
                if(k == 0) {
                    getline(line_stringstream, url1 , ',');
                    first_slash = url1.find_first_of('/');
                    site1 = url1.substr(0,first_slash);
                    id1 = url1.substr(first_slash+2);
                }
                else if(k == 1) {
                    getline(line_stringstream, url2, ',');
                    first_slash = url2.find_first_of('/');
                    site2 = url2.substr(0,first_slash);
                    id2 = url2.substr(first_slash+2);
                }
                else if(k == 2) {
                    getline(line_stringstream, label_str, ',');
                    label = atoi(label_str.c_str());       
                }
            }
            e1 = ht->search(hash_value_calculator(site1, id1));
            e2 = ht->search(hash_value_calculator(site2, id2));

            gradient_descent(e1->loc, e2->loc, label, files);

        }

        std::cout << L << "\t\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;;
        J = (1.0/(float)train_size)*L;
        if( abs(prevL) < abs(L) ) {
            std::cout << "Stoped training at " << j << " iterations (L went up)" << std::endl;
            break;
        }

        float max=0;
        for(int k=0 ; k < weights_size ; ++k) {
            float temp = weights[k];
            weights[k] = weights[k] - (learning_rate*thetaJ[k]);
            float dif = abs((float)temp - (float)weights[k]);
            if( max < dif)
                max = dif; 
        }
        if( max < 0.01 ) {
            std::cout << "Stoped training at " << j << " iterations (weights change < e)" << std::endl;
            break;
        }

    }
}

void LR::predict(SM* files, std::string* test, unsigned int test_size, HashTable* ht) {
    std::cout << "Started testing..." << std::flush;
    int e1, e2;
    std::string url1, url2, label_str;
    short int label;
    std::string word, site1, id1, site2, id2;
    size_t first_slash;
    for(int k=0 ; k < test_size ; ++k) {
        std::stringstream line_stringstream(test[k]);
        for(int i=0 ; i < weights_size ; ++i) {
            thetaJ[i] = 0;
        }
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
        e1 = ht->search(hash_value_calculator(site1, id1))->loc;
        e2 = ht->search(hash_value_calculator(site2, id2))->loc;
    
    
        float f = 0;
        float p;
        float x[weights_size];
        float tf_idf1[weights_size/2] = {0};
        float tf_idf2[weights_size/2] = {0};
        files->get_tfidf_vector(e1, tf_idf1);
        files->get_tfidf_vector(e2, tf_idf2);

        for(int i=0 ; i < weights_size ; ++i) {
            if(i < weights_size/2) {
                x[i] = tf_idf1[i];
                x[i+weights_size/2] = tf_idf2[i];
            }
            f += weights[i]*((float)x[i]);
        }
        p = 1.0/(1.0+exp(-f));

        float dif = abs((float)p - (float)label);
        if(dif < 0.5)
            pred_counter++;
        if(dif < THRESHOLD)
            pred_threshold_counter++;
    }
    
    float pred_perc = 100.0*float(pred_counter)/float(test_size);
    float pred_thre_perc = 100.0*float(pred_threshold_counter)/float(pred_counter);
    std::cout << "\t\t\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;
    std::cout << pred_counter << " correct predictions out of a total of " << test_size << " (" << pred_perc << "%)" << std::endl ;
    std::cout << pred_threshold_counter << " of which are within " << THRESHOLD << " threshold" << " (" << pred_thre_perc << "%)" << std::endl;
}

void LR::validate(SM* files, std::string* validation_set, unsigned int validation_size, HashTable* ht) {
    std::cout << "Started validation..." << std::flush;
    int e1, e2;
    std::string url1, url2, label_str;
    short int label;
    std::string word, site1, id1, site2, id2;
    size_t first_slash;
    for(int k=0 ; k < validation_size ; ++k) {
        std::stringstream line_stringstream(validation_set[k]);
        for(int i=0 ; i < weights_size ; ++i) {
            thetaJ[i] = 0;
        }
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
        e1 = ht->search(hash_value_calculator(site1, id1))->loc;
        e2 = ht->search(hash_value_calculator(site2, id2))->loc;
    
    
        float f = 0;
        float p;
        float x[weights_size];
        float tf_idf1[weights_size/2] = {0};
        float tf_idf2[weights_size/2] = {0};
        files->get_tfidf_vector(e1, tf_idf1);
        files->get_tfidf_vector(e2, tf_idf2);

        for(int i=0 ; i < weights_size ; ++i) {
            if(i < weights_size/2) {
                x[i] = tf_idf1[i];
                x[i+weights_size/2] = tf_idf2[i];
            }
            f += weights[i]*((float)x[i]);
        }
        p = 1.0/(1.0+exp(-f));

        float dif = abs((float)p - (float)label);
        if( dif < 0.5)
            val_counter++;
        if( dif < THRESHOLD)
            val_threshold_counter++;
    }
    
    float val_perc = 100.0*float(val_counter)/float(validation_size);
    float val_thre_perc = 100.0*float(val_threshold_counter)/float(val_counter);
    std::cout << "\t\t\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;
    std::cout << val_counter << " correct predictions out of a total of " << validation_size << " (" << val_perc << "%)" << std::endl ;
    std::cout << val_threshold_counter << " of which are within " << THRESHOLD << " threshold" << " (" << val_thre_perc << "%)" << std::endl;
}

void LR::validate_unknown(SM* files, Clique* single_entries, Clique* list_of_entries) {
    Cliquenode* cn = single_entries->head;
    Entry *e1 = NULL;
    Entry *e2 = NULL;
    std::ofstream output;
    output.open("validation_output.csv");
    output << "left_spec_id,right_spec_id,label\n";

    while( cn != NULL ) {
        e1 = cn->data;
        Cliquenode* cn_all = list_of_entries->head;
        Entry* most_similar_entry = NULL;
        float max = 0;
        float tf_idf1[weights_size/2] = {0};
        files->get_tfidf_vector(e1->loc, tf_idf1);
        while( cn_all != NULL ) {
            e2 = cn_all->data;
            if(e1 != e2) {

                float f = 0;
                float p;
                float tf_idf2[weights_size/2] = {0};
                files->get_tfidf_vector(e2->loc, tf_idf2);

                for(int i=0 ; i < weights_size ; ++i) {
                    if(i < weights_size/2) {
                        f += weights[i]*((float)tf_idf1[i]);
                    }
                    else {
                        f += weights[i]*((float)tf_idf2[i-weights_size/2]);
                    }
                }
                p = 1.0/(1.0+exp(-f));

                if( max < p ) {
                    max = p;
                    most_similar_entry = e2;
                }
            }
            cn_all = cn_all->next;
        }
        std::string url1 = e1->get_page_title() + "//" + e1->get_id();
        std::string url2 = most_similar_entry->get_page_title() + "//" + most_similar_entry->get_id();
        output << url1 << "," << url2 << ",1" <<  "\n";

        cn = cn->next;
    }
    output.close();
}