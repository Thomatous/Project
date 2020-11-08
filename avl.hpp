#ifndef _AVL_
#define _AVL_

#include <iostream>
#include "entry.hpp"

class Treenode{
    private:
        int height;
        Entry *entry;
    public:
        Treenode* left;
        Treenode* right;

        Treenode();
        Treenode(Entry*);
        ~Treenode();
        void set_height(int);
        int get_height();
        int get_entry_hashvalue();
        void update_height();
};

class AVL{
    private:

    public:
        Treenode* root;
        int size;

        AVL();
        ~AVL();
        int get_size();
        int get_balance(Treenode*);
        Treenode* right_rotate(Treenode*);
        Treenode* left_rotate(Treenode*);
        Treenode* insert(Treenode*, Entry*);
};

#endif