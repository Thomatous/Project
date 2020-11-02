#include <iostream>
#include <string>


class Entry{
    private:
        int id;
        std::string page_title;
    public:
        Entry();                        //constructors
        Entry(int);
        Entry(int, std::string);
        ~Entry();                       //destructor
        int get_id();                   //getters
        std::string get_page_table();   
};