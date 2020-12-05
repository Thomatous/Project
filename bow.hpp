#ifndef _BOW_
#define _BOW_

#include <iostream>
#include <string>

struct Bownode {
    std::string data;
    Bownode* next;
};

class Bow{
    private:
        Bownode* head;
        unsigned int size;
    public:
        Bow();
        ~Bow();
        unsigned int get_size();
        bool exists(std::string);
        void push_if_not_exists(std::string);
        void print();
};
#endif