#ifndef _CLIQUE_
#define _CLIQUE_

#include <iostream>
#include "entry.hpp"

class Entry;
struct Cliquenode{
    Entry* data;
    Cliquenode* next;
    Cliquenode(Entry*);
    ~Cliquenode();
};

class Clique{
    private:
        int size;
    public:
        Cliquenode* head;
        Clique();
        ~Clique();
        int get_size();
        bool is_empty();
        void push(Entry*);
        void merge(Clique*);
        bool find(Entry*);
        void print();
};
#endif