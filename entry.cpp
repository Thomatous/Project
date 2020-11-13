#include "entry.hpp"

Entry::Entry(){
    id = "None";                //default value for not initialized id
    page_title = "None";    //dedefault value for not initialized page_tiyle
}

Entry::Entry(std::string new_page_title, std::string new_id){
    id = new_id;           
    page_title = new_page_title;
    clique = new Clique();
    clique->push(this);
    //generating hashvalue for entry
    hashvalue = hash_value_calculator(new_page_title, new_id);
}

Entry::~Entry(){
    delete clique;
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

void Entry::merge(Entry *e){
    clique->merge(e->clique);
    // e->clique = clique;
}
