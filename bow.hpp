#ifndef _BOW_
#define _BOW_

#include <iostream>
#include <string>
#include <sstream>

class Bownode{
    private:
        unsigned int height;
        std::string data;
    public:
        Bownode* left;
        Bownode* right;

        Bownode();
        Bownode(std::string);
        ~Bownode();
        void set_height(int);
        unsigned int get_height();
        std::string get_data();
        void update_height();
};

class Bow{
    private:
        unsigned int size;
    public:
        Bownode* root;
        
        Bow();
        ~Bow();
        void clear(Bownode*);
        unsigned int get_size();
        int get_balance(Bownode*);
        Bownode* right_rotate(Bownode*);
        Bownode* left_rotate(Bownode*);
        Bownode* insert(Bownode*, std::string);
        void print_preorder(Bownode*);
        bool find(Bownode*, std::string);
        Bownode* add(Bownode*, std::string);
};
#endif