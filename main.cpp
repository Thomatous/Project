#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"

int main() {
    std::cout << "Starting..." << std::endl;
    DIR *dir_p;
    DIR *dir_f;
    struct dirent *folder;
    HashTable ht(100);
    Clique list_of_entries;
    Entry* e;
    std::string input_dir = "./Datasets/2013_camera_specs/";
    Parser p;
    Dict all_words;
    // int counter = 0;
    if ( (dir_p = opendir(input_dir.c_str())) == NULL ) {
        perror("can't open the given directory");
        exit(2);
    } else {
        while (folder = readdir(dir_p)) { //read each folder
            if (folder->d_name != std::string(".") && folder->d_name != std::string("..")) {
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
                    while (file = readdir(dir_f)) {
                        if (file->d_name != std::string(".") && file->d_name != std::string("..")) {
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
        }

        (void) closedir (dir_p);
    } 

    // parse csv
    std::ifstream file("./Datasets/sigmod_medium_labelled_dataset.csv");
    std::string line, word = "";

    int first = 0;
    int second = 0;
    for(int i=1 ; i>-1 ; i--) {
        while( getline(file, line) ) { // read every line of the csv
            std::stringstream line_stringstream(line);
            Entry* a = NULL;
            Entry* b = NULL;
            while( getline( line_stringstream, word, ',') ) { //tokenize with delimeter: ","
                // std::cout << word << "\n";
                size_t first_slash = word.find_first_of('/'); //find '/' and strip them
                if ( first_slash == std::string::npos) { //then it's 0 || 1 for similarities
                    if(std::strcmp(word.c_str(), std::to_string(i).c_str()) == 0){    //if products are similar
                        if(a != NULL && b != NULL){ //if both specs have been iterated
                            // std::cout << "Merging:" << std::endl;
                            // a->clique->print();
                            // b->clique->print();
                            if(i == 1) {
                                a->merge(b);    //merge their cliques
                                first++;
                            }
                            if(i == 0) {
                                a->differs_from(b);
                                second++;
                            }
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

        file.clear();
        file.seekg(0);
    }
    int num_entries = list_of_entries.get_size();
    // std::cout << first << std::endl;
    // std::cout << second << std::endl;
    std::cout << "Full dictionary contains " << all_words.get_size() << " unique words." << std::endl;
    int num_words = all_words.get_size();
    
    std::string all_words_vector[num_words];
    float all_idf_vector[num_words];
    unsigned int loc = 0;
    all_words.vectorify(all_words.root, all_words_vector, all_idf_vector, &loc, num_entries);
    std::cout << "Full dictionary vector has been created." << std::endl;

    mergeSort(all_idf_vector, all_words_vector, 0, num_words-1);
    Dict best_words;
    for(int i=0 ; i < DICTIONARY_SIZE ; i++) {
        best_words.root = best_words.insert(best_words.root, all_words_vector[num_words-1-i], all_idf_vector[num_words-1-i]);
    }
    // creating dict anf tf_idf arrays
    int **dict_matrix = new int*[num_entries];
    float **tf_idf = new float*[num_entries];
    for(int i=0 ; i<num_entries ; i++) {
        dict_matrix[i] = new int[DICTIONARY_SIZE];
        tf_idf[i] = new float[DICTIONARY_SIZE];
        for(int j=0 ; j < DICTIONARY_SIZE ; j++) {
            dict_matrix[i][j] = 0;
            tf_idf[i][j] = 0;
        }
    }
    // delete[] dict_vector;
    // delete[] idf_vector;
    std::string best_words_vector[DICTIONARY_SIZE];
    float best_idf_vector[DICTIONARY_SIZE];
    loc = 0;
    best_words.vectorify(best_words.root, best_words_vector, best_idf_vector, &loc);
    // seting values of dict anf tf arrays
    create_bow_and_tf(dict_matrix, tf_idf, &list_of_entries, &best_words);
    // multiplying tf*idf
    for(int i=0 ; i<num_entries ; i++) {
        for(int j=0 ; j<DICTIONARY_SIZE ; j++) {
            tf_idf[i][j] = tf_idf[i][j]*best_idf_vector[j]; 
        }
    }

    // these are for printing
    // for(int i=0 ; i<num_entries ; i++) {
    //     for(int j=0 ; j<DICTIONARY_SIZE ; j++) {
    //         std::cout << tf_idf[i][j] << "\t";
    //     }
    //     std::cout << "\n";
    // }

    // output printing
    std::ofstream output;
    output.open("output.csv");
    output << "left_spec_id,right_spec_id,label\n";
    unsigned int lines_counter = 0;
    Cliquenode* c_n = NULL;
    Clique* c = NULL;
    AntiClique* d = NULL; 
    while( !(list_of_entries.is_empty()) ) {    //parse list of entries
        c_n = list_of_entries.pop();            //pop
        c = c_n->data->clique;                  //get entry's clique
        if( c != NULL) {                         //if not NULL
            int size = c->get_size();
            Cliquenode* table[size];            //create table of clique's members
            for(int i=0 ; i<size ; i++) {
                table[i] = c->pop();
            }

            // print every possible pair from that clique
            for(int i=0 ; i<size ; i++) {       
                std::string url1 = table[i]->data->get_page_title() + "//" + table[i]->data->get_id();
                for(int j=i+1 ; j<size ; j++) {
                    std::string url2 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                    output << url1 << "," << url2 << ",1" <<  "\n";
                    ++lines_counter;
                }
                table[i]->data->clique = NULL;  //make clique pointer NULL for all those entries so we don't print any pair more than once
            }

            // print every possible negative similarity pair of entries
            d = c->different;                           // list of different cliques 
            if ( !d->is_empty() ) {
                int d_size = d->get_size();
                AntiCliquenode* d_table[d_size];
                // adding all different cliques to d_table
                for(int i=0 ; i<d_size ; i++) {
                    d_table[i] = d->pop();
                }

                for(int i=0 ; i<d_size ; i++) {         // for every different clique
                    Clique* d_c = d_table[i]->data;
                    for(int j=0 ; j<size ; j++) {       // for every entry in c clique
                        Cliquenode* d_e = d_c->head;
                        std::string url1 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                        while( d_e != NULL ) {          // for every entry in different clique
                            std::string url2 = d_e->data->get_page_title() + "//" + d_e->data->get_id();
                            output << url1 << "," << url2 << ",0" <<  "\n";
                            ++lines_counter;
                            d_e = d_e->next;
                        }
                    }
                    d_c->different->remove(c);          // after finishing with this different clique, 
                                                        //remove c clique from different clique's different list
                }

                for(int i=0 ; i<d_size ; i++) {
                    delete d_table[i];
                }
            }

            // c->update_clique_ptrs(NULL);
            for(int i=0 ; i<size ; i++) {
                delete table[i];
            }

        }
        delete c;
        delete c_n;
    }

    output.close();

    std::ifstream input;
    input.open("output.csv");
    std::string* dataset = new std::string[lines_counter];
    if ( input.is_open() ) {
        std::string empty;
        getline(input, empty);          // discard header line
        // fill up array with info lines
        for(unsigned int i=0 ; i < lines_counter ; ++i) {
            getline(input, dataset[i]);
        }
    } else {
        perror("no output file");
    }

    // create train, test and validation sets
    shuffle(dataset, lines_counter);
    int train_size = 0.6*lines_counter;
    int test_size = 0.2*lines_counter;
    if( lines_counter > train_size + 2*test_size)
        train_size += lines_counter-(train_size + 2*test_size);
    std::string* train_set = new std::string[train_size];
    std::string* test_set = new std::string[test_size];
    std::string* validation_set = new std::string[test_size];
    for(int i=0 ; i < lines_counter ; ++i) {
        if(i < train_size)
            train_set[i] = dataset[i];
        else if(i < train_size+test_size)
            test_set[i-train_size] = dataset[i];
        else 
            validation_set[i-(train_size+test_size)] = dataset[i];
    }
    delete[] dataset;



    // empty heap
    delete[] train_set;
    delete[] test_set;
    delete[] validation_set;
    for(int i=0 ; i<num_entries ;i++) {
        delete[] dict_matrix[i];
        delete[] tf_idf[i];
    }
    delete[] dict_matrix;
    delete[] tf_idf;

    return 0;
}