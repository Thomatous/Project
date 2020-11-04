#ifndef _ENTRY_
#define _ENTRY_

#include <iostream>
#include <string>


class Entry{
    private:
        std::string id;
        std::string page_title;
        // STRING LIST OF PRODUCTS;       
    public:
        Entry();                            //constructors
        Entry(std::string, std::string);
        Entry(std::string);
        ~Entry();                           //destructor
        std::string get_id();               //getters
        std::string get_page_table();
        void print();                       //misc   
};

#endif