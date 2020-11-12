#ifndef _CLIQUE_
#define _CLIQUE_

#include <iostream>
#include "entry.hpp"

struct Cliquenode{
    Entry* data;
    Cliquenode* next;
    Cliquenode(Entry*);
    ~Cliquenode();
};

class Clique{
    private:
        Cliquenode* head;
        int size;
    public:
        Clique();
        ~Clique();
        int get_size();
        bool is_empty();
        void push(Entry*);
        Cliquenode* merge(Cliquenode*);
        bool find(Entry*);
};
#endif