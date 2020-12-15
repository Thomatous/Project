#ifndef _SPARSE_
#define _SPARSE_

#include <iostream>
#include <string>
#include <sstream>
#include "dict.hpp"
#include "clique.hpp"

struct Wordnode{
    int all_words_pos;
    int best_words_pos;
    int bow;
    float tfidf;
    Wordnode* next;

    Wordnode(int, int, float);
};


class Wordlist{
    private:
        Wordnode* head;
        unsigned int size;
    public: 
        Wordlist();
        ~Wordlist();
        unsigned int get_size();
        void push(int, int, float);
        void push(int, int, int, float);
        Wordnode* pop();                
        void remove_not_best(int *, int);    //parse list and remove nodes with all_words_pos not in given array & update best_words_pos
        // float* vectorify(int);          //create vector of words with given size
        // float get_tfidf(int);           //get tfidf of word with given pos
};

struct SM{
    unsigned int size;
    Wordlist** file_vector;
    
    SM(unsigned int);
    SM(Clique*, float*, float*, Dict*);
    ~SM();
};
#endif