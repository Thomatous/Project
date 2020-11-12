#ifndef _ENTRY_
#define _ENTRY_

#include <iostream>
#include <string>
#include "utility.hpp"
#include "clique.hpp"

class Clique;
class Entry{
    private:
        std::string id;
        std::string page_title;
        unsigned long long hashvalue;
    public:
        Clique* clique;       
        Entry();                            //constructors
        Entry(std::string, std::string);
        ~Entry();                           //destructor
        std::string get_id();               //getters
        std::string get_page_title();
        unsigned long long get_hashvalue();
        void print();                       //misc
        void merge(Entry*);  
};

#endif