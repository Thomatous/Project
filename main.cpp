#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"
#include "dict.hpp"
#include "logistic_regression.hpp"
#include "sparse_matrix.hpp"

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
        std::cout << "Reading the datasets..." << std::flush;
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
        std::cout << "\t\t\t\t\t\t\t\033[1;32mFINISHED\033[0m" << std::endl;        
        (void) closedir (dir_p);
    } 

    // parse csv
    std::ifstream file("./Datasets/sigmod_medium_labelled_dataset.csv");
    std::string line, word = "";

    unsigned int lines_counter = 0;
    unsigned int train_size;
    unsigned int test_size;
    unsigned int counter = 0;
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
        for(int i = 0 ; i < lines_counter ; i++) {
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
        for(int i=0 ; i < lines_counter ; ++i) {
            if(i < train_size)
                cliques_set[i] = dataset[i];
            else if(i < train_size+test_size)
                test_set[i-train_size] = dataset[i];
            else 
                validation_set[i-(train_size+test_size)] = dataset[i];
        }
        delete[] dataset;
        for(int j = 1 ; j >= 0 ; j--) {
            for(int i = 0 ; i < train_size ; i++) {
                std::stringstream line_stringstream(cliques_set[i]);
                Entry* a = NULL;
                Entry* b = NULL;
                while( getline( line_stringstream, word, ',') ) { //tokenize with delimeter: ","
                    // std::cout << word << "\n";
                    size_t first_slash = word.find_first_of('/'); //find '/' and strip them
                    if ( first_slash == std::string::npos) { //then it's 0 || 1 for similarities
                        if(std::strcmp(word.c_str(), std::to_string(j).c_str()) == 0){    //if products are similar
                            if(a != NULL && b != NULL){ //if both specs have been iterated
                                // std::cout << "Merging:" << std::endl;
                                // a->clique->print();
                                // b->clique->print();
                                if(j == 1) {
                                    a->merge(b);    //merge their cliques
                                }
                                if(j == 0) {
                                    a->differs_from(b);
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
    int best_words_number = 500;
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

    // output printing
    std::ofstream output;
    output.open("output.csv");
    output << "left_spec_id,right_spec_id,label\n";
    unsigned int output_lines_counter = 0;
    Cliquenode* c_n = list_of_entries.head;
    Clique* c = NULL;
    AntiClique* d = NULL; 
    while( c_n != NULL ) {    //parse list of entries
        c = c_n->data->clique;                  //get entry's clique
        int size = c->size;
        if( c->printed == false ) {                         //if not NULL
            
            Cliquenode* table[size];            //create table of clique's members
            Cliquenode* temp_entry = c->head;
            for(int i=0 ; i < size ; i++) {
                table[i] = temp_entry;
                temp_entry = temp_entry->next;
            }

            // print every possible pair from that clique
            for(int i=0 ; i<size ; i++) {       
                std::string url1 = table[i]->data->get_page_title() + "//" + table[i]->data->get_id();
                for(int j=i+1 ; j<size ; j++) {
                    std::string url2 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                    output << url1 << "," << url2 << ",1" <<  "\n";
                    ++lines_counter;
                }
                // table[i]->data->clique = NULL;  //make clique pointer NULL for all those entries so we don't print any pair more than once
            }
            c->printed = true;

            // print every possible negative similarity pair of entries
            d = c->different;                           // list of different cliques 
            if ( !d->is_empty() ) {
                // std::cout << d->size << std::endl;
                int d_size = d->size;
                
                if(c->anti_printed == NULL){
                    c->anti_printed = new Clique*[d_size];
                    for(int i=0 ; i < d_size ; i++) c->anti_printed[i] = NULL;
                }
            
                // adding all different cliques to d_table
                AntiCliquenode* d_table[d_size];
                AntiCliquenode* temp_d = d->head;
                for(int i=0 ; i<d_size ; i++) {
                    d_table[i] = temp_d;
                    temp_d = temp_d->next;
                }                

                for(int i=0 ; i<d_size ; i++) {         // for every different clique
                    Clique* d_c = d_table[i]->data;
                    
                    int d_c_size = d_c->size;
                    
                    if(d_c->anti_printed == NULL){
                        d_c->anti_printed = new Clique*[d_c->different->size];
                        for(int i=0 ; i < d_c->different->size ; i++) d_c->anti_printed[i] = NULL;
                    }

                    bool continue_flag = false;
                    for(int j = 0 ; j < d_size ; j++){
                        if(c->anti_printed[j] == d_c){
                            continue_flag = true;
                            break;
                        }
                    }
                    if(continue_flag == true) {
                        continue;    
                    } else {
                        for(int j = 0 ; j < d_size ; j++){
                            if(c->anti_printed[j] == NULL){
                                c->anti_printed[j] = d_c;
                                break;
                            }
                        }
                        for(int j = 0 ; j < d_c->different->size ; j++) {
                            if(d_c->anti_printed[j] == NULL){
                                d_c->anti_printed[j] = c;
                                break;
                            }
                        }
                    }


                    for(int j=0 ; j<size ; j++) {       // for every entry in c clique
                        Cliquenode* d_e = d_c->head;
                        std::string url1 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                        while( d_e != NULL ) {          // for every entry in different clique
                            std::string url2 = d_e->data->get_page_title() + "//" + d_e->data->get_id();
                            output << url1 << "," << url2 << ",0" <<  "\n";
                            ++output_lines_counter;
                            d_e = d_e->next;
                        }
                    }
                }
            }
        }
        c_n = c_n->next;
    }
    output.close();

    std::ifstream input;
    input.open("output.csv");
    std::string* train_set = new std::string[output_lines_counter];
    if ( input.is_open() ) {
        std::string empty;
        getline(input, empty);          // discard header line
        // fill up array with info lines
        for(unsigned int i=0 ; i < output_lines_counter ; ++i) {
            getline(input, train_set[i]);
        }
    } else {
        perror("no output file");
    }
    input.close();

    LR* lr = new LR(best_words_number*2);
    lr->train(&files, train_set, output_lines_counter, 650, &ht);
    lr->predict(&files, test_set, test_size, &ht);
    // lr->train(dict_matrix, train_set, train_size, 0.001, &ht);
    lr->validate(&files, validation_set, test_size, &ht);

    // empty heap
    delete lr;
    delete[] train_set;
    delete[] test_set;
    delete[] validation_set;

    return 0;
}