#include <iostream>
#include <string>


class Entry{
    private:
        int id;
        std::string page_title;
        // STRING LIST OF PRODUCTS;       
    public:
        Entry();                        //constructors
        Entry(int, std::string);
        Entry(std::string);
        ~Entry();                       //destructor
        int get_id();                   //getters
        std::string get_page_table();
        void print();                   //misc   
};