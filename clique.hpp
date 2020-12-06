#ifndef _CLIQUE_
#define _CLIQUE_

#include <iostream>
#include "entry.hpp"
#include "anticlique.hpp"

class Entry;
class AntiClique;
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
        AntiClique* different;
        Clique();
        ~Clique();
        int get_size();
        bool is_empty();
        void push(Entry*);
        Cliquenode* pop();
        void merge(Clique*);
        void merge_different(Clique* c);
        bool find(Entry*);
        void print();
        void update_clique_ptrs(Clique*);
};

#endif