#ifndef _BOW_
#define _BOW_

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>  

#define DICTIONARY_SIZE 3000

class Bownode{
    private:
        unsigned int height;
        std::string data;
        int vector_loc;
    public:
        int idf_count;
        std::string* last_string;

        Bownode* left;
        Bownode* right;

        Bownode();
        Bownode(std::string);
        ~Bownode();
        void set_height(int);
        void set_vector_loc(unsigned int);
        unsigned int get_height();
        std::string get_data();
        void update_height();
        int get_vector_loc();
};

class Bow{
    private:
        unsigned int size;
    public:
        Bownode* root;
        
        Bow();
        ~Bow();
        void clear(Bownode*);
        unsigned int get_size();
        int get_balance(Bownode*);
        Bownode* right_rotate(Bownode*);
        Bownode* left_rotate(Bownode*);
        Bownode* insert(Bownode*, std::string, std::string*);
        Bownode* add(Bownode*, std::string, std::string*);
        void print_preorder(Bownode*);
        bool find(Bownode*, std::string);
        void vectorify(Bownode*, std::string*, float*, unsigned int*, unsigned int);
        int find_loc(Bownode*, std::string);
        void set_word_loc(Bownode*, std::string, int);
};
#endif