#ifndef _DICT_
#define _DICT_

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>  

#define DICTIONARY_SIZE 3000

class Dictnode{
    private:
        unsigned int height;
        std::string data;
        int vector_loc;
    public:
        int idf_count;
        float idf;
        std::string* last_string;

        Dictnode* left;
        Dictnode* right;

        Dictnode();
        Dictnode(std::string);
        ~Dictnode();
        void set_height(int);
        void set_vector_loc(unsigned int);
        unsigned int get_height();
        std::string get_data();
        void update_height();
        int get_vector_loc();
};

class Dict{
    private:
        unsigned int size;
    public:
        Dictnode* root;
        
        Dict();
        ~Dict();
        void clear(Dictnode*);
        unsigned int get_size();
        int get_balance(Dictnode*);
        Dictnode* right_rotate(Dictnode*);
        Dictnode* left_rotate(Dictnode*);
        Dictnode* insert(Dictnode*, std::string, std::string*);
        Dictnode* insert(Dictnode*, std::string, float);
        Dictnode* add(Dictnode*, std::string, std::string*);
        void print_preorder(Dictnode*);
        bool find(Dictnode*, std::string);
        void vectorify(Dictnode*, std::string*, float*, float*, unsigned int*, unsigned int);
        void vectorify(Dictnode*, std::string*, float*, unsigned int*);
        int find_loc(Dictnode*, std::string);
        void set_word_loc(Dictnode*, std::string, int);
};
#endif