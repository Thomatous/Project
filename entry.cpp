#include "entry.hpp"

Entry::Entry(){
    id = -1;                //default value for not initialized id
    page_title = "None";    //dedefault value for not initialized page_tiyle
}

Entry::Entry(int new_id, std::string new_page_title){
    id = new_id;           
    page_title = new_page_title;  
}

Entry::Entry(std::string fullname){
    //code to break string into id and page_title
}

Entry::~Entry(){
    //call destructor for product list
}

int Entry::get_id(){
    return id;
}

std::string Entry::get_page_table(){
    return page_title;
}

void Entry::print(){
    std::cout << page_title << "//" << id << std::endl;
}
