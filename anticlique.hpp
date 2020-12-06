#ifndef _ANTICLIQUE_
#define _ANTICLIQUE_

#include <iostream>
#include "clique.hpp"

class Clique;

struct AntiCliquenode {
    Clique* data;
    AntiCliquenode* next;
    AntiCliquenode(Clique*);
    ~AntiCliquenode();
};

class AntiClique{
    private:
        int size;
    public:
        AntiCliquenode* head;
        AntiClique();
        ~AntiClique();
        int get_size();
        bool is_empty();
        void push(Clique*);
        AntiCliquenode* pop();
        void merge(AntiClique*);
        bool find(Clique*);
};

#endif