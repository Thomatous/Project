#ifndef _PARSERLIST_
#define _PARSERLIST_

#include <iostream>
#include <string>

struct Parserlistnode{
    std::string var_name;
    std::string var_content;
    Parserlistnode *next;
    Parserlistnode(std::string, std::string);
};

class Parserlist{
    private:
        Parserlistnode *head;
        int size;
    public:
        Parserlist();
        ~Parserlist();
        int get_size();
        void push(std::string, std::string);
        void print();
};
#endif