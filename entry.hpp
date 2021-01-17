#ifndef _ENTRY_
#define _ENTRY_

#include <iostream>
#include <string>
#include "utility.hpp"
#include "clique.hpp"
#include "parserlist.hpp"
#include "connection_tree.hpp"

class ConnectionTree;
class Clique;
class Entry{
    private:
        std::string id;
        std::string page_title;
        unsigned long long hashvalue;
        Parserlist* specs;
    public:
        std::string specs_words;
        int loc; 
        Clique* clique;

        ConnectionTree *conn_tree;

        Entry();                            //constructors
        Entry(std::string, std::string);
        Entry(std::string, std::string, Parserlist*);
        ~Entry();                           //destructor
        std::string get_id();               //getters
        std::string get_page_title();
        Parserlist* get_specs();
        unsigned long long get_hashvalue();
        void print();                       //misc
        void merge(Entry*);
        void differs_from(Entry *e);
};

#endif