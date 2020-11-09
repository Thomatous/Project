#include "entry.hpp"

Entry::Entry(){
    id = "None";                //default value for not initialized id
    page_title = "None";    //dedefault value for not initialized page_tiyle
}

Entry::Entry(std::string new_page_title, std::string new_id){
    id = new_id;           
    page_title = new_page_title;

    //generating hashvalue for entry
    hashvalue = 5381;

    int c;
    const char* site_c = page_title.c_str();
    const char* id_c = id.c_str();

    while (c = *site_c++)
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */

    while (c = *id_c++)
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */
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

unsigned long long Entry::get_hashvalue(){
    return hashvalue;
}

void Entry::print(){
    std::cout << page_title << "//" << id << std::endl;
}
