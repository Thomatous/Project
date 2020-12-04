#include "entry.hpp"

Entry::Entry(){
    id = "None";                //default value for not initialized id
    page_title = "None";        //dedefault value for not initialized page_tiyle
}

//constructor for entries
//assignes values given
Entry::Entry(std::string new_page_title, std::string new_id){
    id = new_id;           
    page_title = new_page_title;
    clique = new Clique();
    clique->push(this);
    different = new Clique();
    specs = NULL;
    //generating hashvalue for entry
    hashvalue = hash_value_calculator(new_page_title, new_id);
}

Entry::Entry(std::string new_page_title, std::string new_id, Parserlist* list){
    id = new_id;           
    page_title = new_page_title;
    clique = new Clique();
    clique->push(this);
    different = new Clique();
    specs = list;
    //generating hashvalue for entry
    hashvalue = hash_value_calculator(new_page_title, new_id);
}

//entry destructor
Entry::~Entry(){
    if(clique != NULL)
        delete clique;
    if(different != NULL)
        delete different;
    if(specs != NULL)
        delete specs;
}

//id getter
std::string Entry::get_id(){
    return id;
}

//page title getter
std::string Entry::get_page_title(){
    return page_title;
}

Parserlist* Entry::get_specs() {
    return specs;
}

//hashvalue getter
unsigned long long Entry::get_hashvalue(){
    return hashvalue;
}

//debug function prints entry strings
void Entry::print(){
    std::cout << page_title << "//" << id << std::endl;
}

//merges the clique of this entry with the given entry's clique
void Entry::merge(Entry *e){
    if(e->clique != clique){
        clique->merge(e->clique);           //call clique merrge
        clique->update_clique_ptrs(clique); //make all entries in the clique point to this new merged one

        different->merge(e->different);
        clique->update_different_ptrs(different);
    }
}

//pushes given entry in different clique or merges the different clique of this entry with the given entry's different clique
void Entry::differs_from(Entry *e) {
    if( e->different != different ) {
        different->merge_different(e->clique);
        // different->update_different_ptrs(different);

        e->different->merge_different(clique);
        // e->different->update_different_ptrs(e->different);
    }
}