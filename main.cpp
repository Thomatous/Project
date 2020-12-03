#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "entry.hpp"
#include "hashtable.hpp"
#include "parser.hpp"

int main() {
    DIR *dir_p;
    DIR *dir_f;
    struct dirent *folder;
    HashTable ht(100);
    Clique list_of_entries;
    Entry* e;
    std::string input_dir = "./Datasets/2013_camera_specs/";
    Parser p;
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
    std::ifstream file("./Datasets/sigmod_large_labelled_dataset.csv");
    std::string line, word = "";

    while( getline(file, line) ) { // read every line of the csv
        std::stringstream line_stringstream(line);
        Entry* a = NULL;
        Entry* b = NULL;
        while( getline( line_stringstream, word, ',') ) { //tokenize with delimeter: ","
            // std::cout << word << "\n";
            size_t first_slash = word.find_first_of('/'); //find '/' and strip them
            if ( first_slash == std::string::npos) { //then it's 0 || 1 for similarities
                if(std::strcmp(word.c_str(), "1") == 0){    //if products are similar
                    if(a != NULL && b != NULL){ //if both specs have been iterated
                        // std::cout << "Merging:" << std::endl;
                        // a->clique->print();
                        // b->clique->print();
                        a->merge(b);    //merge their cliques
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

    // output printing
    std::ofstream output;
    output.open("output.csv");
    output << "left_spec_id,right_spec_id\n";
    Cliquenode* c_n = NULL;
    Clique* c = NULL;
    while( !(list_of_entries.is_empty()) ) {    //parse list of entries
        c_n = list_of_entries.pop();            //pop
        c = c_n->data->clique;                  //get entry's clique
        if( c!= NULL) {                         //if not NULL
            int size = c->get_size();
            Cliquenode* table[size];            //create table of clique's members
            for(int i=0 ; i<size ; i++) {
                table[i] = c->pop();
            }
            for(int i=0 ; i<size ; i++) {       //print every possible pair from that clique
                std::string url1 = table[i]->data->get_page_title() + "//" + table[i]->data->get_id();
                for(int j=i+1 ; j<size ; j++) {
                    std::string url2 = table[j]->data->get_page_title() + "//" + table[j]->data->get_id();
                    output << url1 << "," << url2 << "\n";
                }
                table[i]->data->clique = NULL;  //make clique pointer NULL for all those entries so we don't print any pair more than once
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
    
    return 0;
}