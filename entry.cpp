#include "entry.hpp"

Entry::Entry(){
    id = "None";                //default value for not initialized id
    page_title = "None";    //dedefault value for not initialized page_tiyle
}

Entry::Entry(std::string new_id, std::string new_page_title){
    id = new_id;           
    page_title = new_page_title;
    
    int ascii_sum = 0;
    for (int i = 0; i < page_title.size(); i++) { 
        ascii_sum += (int)(page_title[i]); 
    }
    hashvalue = ascii_sum + std::stoi(id);
}

Entry::~Entry(){
    //call destructor for product list
}

std::string Entry::get_id(){
    return id;
}

std::string Entry::get_page_title(){
    return page_title;
}

int Entry::get_hashvalue(){
    return hashvalue;
}

void Entry::print(){
    std::cout << page_title << "//" << id << std::endl;
}
