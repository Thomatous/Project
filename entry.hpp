#ifndef _ENTRY_
#define _ENTRY_

#include <iostream>
#include <string>


class Entry{
    private:
        std::string id;
        std::string page_title;
        int hashvalue;
        // STRING LIST OF PRODUCTS;       
    public:
        Entry();                            //constructors
        Entry(std::string, std::string);
        ~Entry();                           //destructor
        std::string get_id();               //getters
        std::string get_page_title();
        int get_hashvalue();
        void print();                       //misc   
};

#endif