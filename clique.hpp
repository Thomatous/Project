#ifndef _CLIQUE_
#define _CLIQUE_

#include <iostream>
#include "entry.hpp"
#include "anticlique.hpp"
#include <sstream>
#include <string>

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
    public:
        int size;
        bool printed;
        bool destroyed;
        Clique** anti_printed;

        Cliquenode* head;
        AntiClique* different;
        Clique();
        ~Clique();
        int get_size();
        bool is_empty();
        void push(Entry*);
        void push(Cliquenode*);
        Cliquenode* pop();
        void merge(Clique*);
        void merge_different(Clique*);
        void replace_different(Clique*);
        bool find(Entry*);
        void print();
        void update_clique_ptrs(Clique*);
        void destroy();
};

#endif