#ifndef _AVL_
#define _AVL_

#include <iostream>
#include "entry.hpp"

class Treenode{
    private:
        unsigned int height;
        Entry *entry;
    public:
        Treenode* left;
        Treenode* right;

        Treenode();
        Treenode(Entry*);
        ~Treenode();
        void set_height(int);
        unsigned int get_height();
        unsigned long long get_entry_hashvalue();
        Entry* get_entry();
        void update_height();
};

class AVL{
    private:
        unsigned int size;
    public:
        Treenode* root;
        
        AVL();
        ~AVL();
        void clear(Treenode*);
        unsigned int get_size();
        int get_balance(Treenode*);
        Treenode* right_rotate(Treenode*);
        Treenode* left_rotate(Treenode*);
        Treenode* insert(Treenode*, Entry*);
        void print_preorder(Treenode*);
        Entry* search(Treenode*, unsigned long long);
};

#endif