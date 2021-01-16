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
    public:
        int size;
        bool destroyed;
        AntiCliquenode* head;
        AntiClique();
        ~AntiClique();
        int get_size();
        bool is_empty();
        void push(Clique*);
        void push(AntiCliquenode*);
        AntiCliquenode* pop();
        void merge(AntiClique*);
        bool find(Clique*);
        void remove(Clique*);
        void replace(Clique*, Clique*);
        void destroy();
};

#endif