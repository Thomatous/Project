#ifndef _SPARSE_
#define _SPARSE_

#include <iostream>

struct Wordnode{
    int all_words_pos;
    int best_words_pos;
    float tfidf;
    float bow;
    Wordnode* next;

    Wordnode(int, float, float);
};


class Wordlist{
    private:
        Wordnode* head;
        unsigned int size;
    public: 
        Wordlist();
        ~Wordlist();
        unsigned int get_size();
        void push(int, float, float);
        void push(int, int, float, float);
        Wordnode* pop();                
        void remove_not_best(int *, int);    //parse list and remove nodes with all_words_pos not in given array & update best_words_pos
        // float* vectorify(int);          //create vector of words with given size
        // float get_tfidf(int);           //get tfidf of word with given pos
};

struct SM{
    unsigned int size;
    Wordlist** file_vector;
    
    SM(unsigned int);
    ~SM();
};
#endif