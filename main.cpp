#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <csignal>
#include <thread>
#include <mutex>

#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"
#include "logistic_regression.hpp"
#include "sparse_matrix.hpp"
#include "job_scheduler.hpp"
#include "double_linked_list.hpp"
#include <time.h>

int main() {
    std::cout << "learning rate = " << LEARNING_RATE << " batch size = " << BATCH_SIZE << std::endl;

    std::cout << "Starting..." << std::endl;
    
    JobScheduler js(4);
    
    DIR *dir_p;
    DIR *dir_f;
    struct dirent *folder;
    HashTable ht(100);
    Clique list_of_entries;
    Entry* e;
    std::string input_dir = "./Datasets/2013_camera_specs/";
    Parser p;
    Dict all_words;
    unsigned int json_counter = 0;
    // int counter = 0;
    if ( (dir_p = opendir(input_dir.c_str())) == NULL ) {
        perror("can't open the given directory");
        exit(2);
    } else {
        std::cout << "Reading the datasets..." << std::flush;
        while ( (folder = readdir(dir_p)) ) { //read each folder
            if (folder->d_name != std::string(".") && folder->d_name != std::string("..")) {
                // NOTE: REPLACE WITH JOB SCHEDULE ADD 

                // std::cout << "folder = " << folder->d_name << std::endl;
                // for each json use name for constructor
                std::string file_dir = "./Datasets/2013_camera_specs/";
                file_dir.append(folder->d_name); //create every folders path
                // std::cout << file_dir << "\n";
                struct dirent *file;
                if ( (dir_f = opendir(file_dir.c_str())) == NULL ) { //open the created folder path to access jsons
                    perror("can't open the given directory");
                    exit(2);
                } else {
                    while ( (file = readdir(dir_f)) ) {
                        if (file->d_name != std::string(".") && file->d_name != std::string("..")) {
                            json_counter++;
                            // std::cout << "folder = " << folder->d_name << "file = " << file->d_name << std::endl;
                            std::string id_str = file->d_name; //keep id of product from file's title
                            size_t lastdot = id_str.find_last_of(".");
                            if (lastdot == std::string::npos) {
                                // call entry constructor and insert to entry_list and hashtable
                                e = new Entry(std::string(folder->d_name), id_str);
                                list_of_entries.push(e);
                                ht.insert(e);
                            } else {
                                std::string id = id_str.substr(0, lastdot);
                                // std::cout << "folder = " << folder->d_name << " file = " << id_str << std::endl;
                                // call entry constructor and insert to entry_list and hashtable
                                std::string path = file_dir+"/"+id_str;
                                e = new Entry(std::string(folder->d_name), id, p.parse(path));
                                e->specs_words = e->get_specs()->clean_up();
                                // std::cout << counter << std::endl;
                                // counter++;
                                all_words.root = all_words.add(all_words.root, e->specs_words, &(e->specs_words));
                                // e->get_specs()->print();
                                list_of_entries.push(e);
                                ht.insert(e);
                            }
                        }
                    }

                    (void) closedir (dir_f);
                }
            }

            // NOTE: RUN TASKS 
        }
        std::cout << "\t\t\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;        
        (void) closedir (dir_p);
    } 

    // parse csv
    std::ifstream file("./Datasets/sigmod_medium_labelled_dataset.csv");
    std::string line, word = "";

    unsigned int lines_counter = 0;
    unsigned int train_size;
    unsigned int test_size;
    // unsigned int counter = 0;
    std::string* dataset;
    std::string* cliques_set;
    std::string* test_set;
    std::string* validation_set;
    if(file.is_open()) {
        while( getline(file, line) ) {
            lines_counter++;
        }
        lines_counter--;
        dataset = new std::string[lines_counter];
        file.clear();
        file.seekg(0);
        std::string empty;
        getline(file, empty);
        for(unsigned int i = 0 ; i < lines_counter ; i++) {
            getline(file, dataset[i]);
        }
        train_size = 0.6*lines_counter;
        test_size = 0.2*lines_counter;
        if( lines_counter > train_size + 2*test_size)
            train_size += lines_counter-(train_size + 2*test_size);
        cliques_set = new std::string[train_size];
        test_set = new std::string[test_size];
        validation_set = new std::string[test_size];
        shuffle(dataset, lines_counter);
        for(unsigned int i=0 ; i < lines_counter ; ++i) {
            if(i < train_size)
                cliques_set[i] = dataset[i];
            else if(i < train_size+test_size)
                test_set[i-train_size] = dataset[i];
            else 
                validation_set[i-(train_size+test_size)] = dataset[i];
        }
        delete[] dataset;
        for(unsigned int i = 0 ; i < train_size ; i++) {
            std::stringstream line_stringstream(cliques_set[i]);
            Entry* a = NULL;
            Entry* b = NULL;
            while( getline( line_stringstream, word, ',') ) { //tokenize with delimeter: ","
                // std::cout << word << "\n";
                size_t first_slash = word.find_first_of('/'); //find '/' and strip them
                if ( first_slash == std::string::npos) { //then it's 0 || 1 for similarities
                    if(a != NULL && b != NULL){ //if both specs have been iterated
                        // std::cout << "Merging:" << std::endl;
                        // a->clique->print();
                        // b->clique->print();
                        a->conn_tree->root = a->conn_tree->insert(a->conn_tree->root, b);
                        b->conn_tree->root = b->conn_tree->insert(b->conn_tree->root, a);
                        
                        if( word == "1" ) {
                            a->merge(b);    //merge their cliques
                        }
                        else if( word == "0" ) {
                            a->differs_from(b);
                        }
                    }
                } else { // then it's a products url
                    std::string site = word.substr(0,first_slash);
                    std::string id = word.substr(first_slash+2);
                    // std::cout << site << " " << id << "\n";
                    unsigned long long hash_value = hash_value_calculator(site, id);
                    if(a == NULL) {
                        a = ht.search(hash_value);  //find this entry in hashtable 
                        // std::cout<<"a: ";
                        // a->print();
                        // std::cout<<std::endl;
                        // a->clique->print();
                    }
                    else{
                        b = ht.search(hash_value);  //find this entry in hashtable 
                        // std::cout<<"b: ";
                        // b->print();
                        // std::cout<<std::endl;
                        // b->clique->print();
                    } 
                }

            }

        }
        delete[] cliques_set;
        file.close();

    } else {
        perror("could not open dataset W");
    }
    
    std::cout << "Full dictionary contains " << all_words.get_size() << " unique words." << std::endl;
    int num_entries = list_of_entries.size;
    int num_words = all_words.get_size();
    std::string all_words_vector[num_words];
    float all_idf_vector[num_words];
    float all_tfidf_sum_vector[num_words];

    std::cout << "Vectorifying the full dictionary..." << std::flush;
    unsigned int loc = 0;
    
    all_words.vectorify(all_words.root, all_words_vector, all_idf_vector, all_tfidf_sum_vector, &loc, num_entries);
    std::cout << "\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;

    std::cout << "Generating bow and tdifd sparse matrices for all words..." << std::flush;
    SM files(&list_of_entries, all_words_vector, all_tfidf_sum_vector, all_idf_vector, &all_words);
    std::cout << "\t\t\033[1;32mFINISHED\033[0m" << std::endl;
   
    std::cout << "Sorting words based on tfidf sums..." << std::flush;
    int best_words_pos_vector[num_words];
    for(int i = 0 ; i < num_words ; i++) best_words_pos_vector[i] = i;
    mergeSort(all_tfidf_sum_vector, best_words_pos_vector, 0, num_words-1);
    std::cout << "\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;

    std::cout << "Inserting best words in a dictionary..." << std::flush;
    unsigned int best_words_number = 500;
    Dict* best_words = new Dict();
    for(unsigned int i = 0 ; i < best_words_number ; i++){
        int j = best_words_pos_vector[num_words-1-i]; 
        best_words->root = best_words->insert(best_words->root, all_words_vector[j], j, i);
    }
    std::cout << "\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;

    std::cout << "Removing words that aren't best from sparse matrices..." << std::flush;
    files.remove_not_best(best_words);
    delete best_words;
    std::cout << "\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;

    // Clique single_entries;
    // output printing
    unsigned int output_lines_counter = 0;
    print_output(&list_of_entries, &output_lines_counter);

    std::ifstream input;
    input.open("output.csv");
    std::string* train_set = new std::string[output_lines_counter];
    if ( input.is_open() ) {
        std::string empty;
        getline(input, empty);          // discard header line
        // fill up array with info lines
        for(unsigned int i=0 ; i < output_lines_counter ; ++i) {
            // NOTE: add read_output_Job to queue
            getline(input, train_set[i]);
            // pthread_mutex_t* mutex;
            // pthread_mutex_init(mutex, NULL);
            // read_output_Job roj(train_set, &input, i, mutex);
            // roj.run();
        }
        // NOTE: run reading output jobs
    } else {
        perror("no output file");
    }
    input.close();

    // Creating array of all entries
    Cliquenode* temp = list_of_entries.head;
    unsigned int size = list_of_entries.size;
    Entry** entries_array = new Entry*[size];
    for(unsigned int i=0 ; i < size ; ++i) {
        entries_array[i] = temp->data;
        temp = temp->next;
    }

    LR* lr = new LR(best_words_number*2);

    float threshold = 0.03;
    Entry *e1, *e2;
    DoubleLinkedList* results = new DoubleLinkedList();
    for(unsigned int i=0 ; i < 1 ; ++i) {
        lr->train(&files, train_set, output_lines_counter, &ht, &js);
        for(unsigned int j=0 ; j < size ; ++j) {
            e1 = entries_array[i];
            for(unsigned int k=j+1 ; k < size ; ++k) {
                e2 = entries_array[k];
                if( !e1->conn_tree->find(e1->conn_tree->root, e2) ) {
                    js.submit_job(new lr_retrain_Job(e1, e2, &files, results, lr, threshold));
                    if( (j*size+k) % 1000000 == 0) {
                        js.execute_all_jobs();
                        js.wait_all_tasks_finish();
                        // std::cout << "Pairs checked " << j << " Results added: " << results->size << std::endl;
                    }
                }
            }
        }
        if( js.q->size > 0 ) {
            js.execute_all_jobs();
            js.wait_all_tasks_finish();
        }
        std::cout << "Etries to add: " << results->size << std::endl;
        DoubleLinkedNode** results_array = new DoubleLinkedNode*[results->size];
        unsigned int results_size = results->size;
        for(unsigned int j=0 ; j < results_size ; ++j) {
            results_array[j] = results->pop();
        }
        delete results;
        prediction_mergeSort(results_array, 0, results_size-1);
        for(unsigned int j=0 ; j < results_size ; ++j) {
            e1 = results_array[j]->A;
            e2 = results_array[j]->B;
            if( results_array[j]->pred > 0.5 ) {
                if( !(e1->clique->different->find(e2->clique)) ) {
                    e1->merge(e2);
                    e1->conn_tree->insert(e1->conn_tree->root, e2);
                    e2->conn_tree->insert(e2->conn_tree->root, e1);
                }
            } else {
                if( !(e1->clique->find(e2)) ) {
                    e1->differs_from(e2);
                    e1->conn_tree->insert(e1->conn_tree->root, e2);
                    e2->conn_tree->insert(e2->conn_tree->root, e1);
                }
            }
        }
        // print output
        // create new train set by reading output
        // increment threshold

    }

    
    
    
    
    
    lr->predict(&files, test_set, test_size, &ht);
    // lr->train(dict_matrix, train_set, train_size, 0.001, &ht);
    lr->validate(&files, validation_set, test_size, &ht);
    // std::cout << single_entries.size << std::endl;
    // lr->validate_unknown(&files, &single_entries, &list_of_entries);

    // empty heap
    delete lr;
    delete[] train_set;
    delete[] test_set;
    delete[] validation_set;
    return 0;
}